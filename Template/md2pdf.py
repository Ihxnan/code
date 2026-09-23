#!/usr/bin/env python3
"""打印/*.md -> 打印/pdf/*.pdf（带页号），并合并为 打印/pdf/ACM模板合集.pdf

- 每个模板(## 小节)从新的一页开始
- 单文件页脚: "N / 本文件总页数"; 合集页脚: 连续 "N / 总页数"
- 合集带书签: 一级=分类(5个md), 二级=各模板(## 标题)

依赖: pandoc, chromium, pdftotext(poppler), python: pypdf + reportlab
  pip install --user --break-system-packages pypdf reportlab
用法: python3 md2pdf.py
"""
import io, re, subprocess, sys, tempfile
from pathlib import Path

from pypdf import PdfReader, PdfWriter
from reportlab.lib.colors import Color
from reportlab.pdfgen import canvas

SRC = Path(__file__).resolve().parent
DST = SRC / "pdf"
DST.mkdir(exist_ok=True)
MERGED = DST / "ACM模板合集.pdf"

CSS = """
@page { size: A4; margin: 13mm 11mm 16mm; }
* { box-sizing: border-box; }
body {
  font-family: 'Noto Sans CJK SC', 'Source Han Sans CN', sans-serif;
  font-size: 9.5pt; line-height: 1.55; color: #1a1a1a; margin: 0;
}
h1 { font-size: 19pt; margin: 0 0 0.4em; border-bottom: 2.5px solid #2b2b2b; padding-bottom: 6px; }
h2 {
  break-before: page; page-break-before: always;
  font-size: 14.5pt; margin: 0 0 0.5em;
  border-bottom: 1.5px solid #888; padding-bottom: 4px;
}
h3 { font-size: 11.5pt; margin: 1em 0 0.35em; }
h1, h2, h3, h4 { break-after: avoid; page-break-after: avoid; }
p { margin: 0.4em 0; }
pre {
  font-family: 'JetBrains Maple Mono', 'Noto Sans Mono CJK SC', monospace;
  font-size: 8.3pt; line-height: 1.42;
  background: #f6f8fa; border: 1px solid #d8dde3; border-radius: 4px;
  padding: 7px 9px; margin: 0.45em 0;
  white-space: pre-wrap; word-break: break-all;
}
code { font-family: inherit; }
:not(pre) > code {
  background: #eef0f2; border-radius: 3px; padding: 0 3px; font-size: 0.92em;
}
blockquote {
  margin: 0.5em 0; padding: 4px 10px;
  border-left: 3px solid #7a7a7a; background: #f7f7f7; color: #333;
}
blockquote p { margin: 0.25em 0; }
table { border-collapse: collapse; width: 100%; margin: 0.5em 0; font-size: 8.8pt; }
th, td { border: 1px solid #bbb; padding: 3px 7px; text-align: left; }
th { background: #ececec; }
ul, ol { margin: 0.35em 0; padding-left: 1.6em; }
li { margin: 0.18em 0; }
a { color: #0645ad; text-decoration: none; }
hr { border: none; border-top: 1px solid #ccc; }
"""


def md_to_pdf(md: Path, out: Path):
    """md -> chromium 打印为 pdf（h2 分页由 CSS 保证）"""
    html_body = subprocess.run(
        ["pandoc", str(md), "-f", "gfm", "-t", "html5", "--highlight-style", "kate"],
        capture_output=True, text=True, check=True).stdout
    html = (f'<!DOCTYPE html><html lang="zh-CN"><head><meta charset="utf-8">'
            f'<title>{md.stem}</title><style>{CSS}</style></head>'
            f'<body>{html_body}</body></html>')
    tmp = Path(tempfile.mkdtemp()) / f"{md.stem}.html"
    tmp.write_text(html, encoding="utf-8")
    subprocess.run(
        ["chromium", "--headless", "--no-sandbox", "--disable-gpu",
         "--no-pdf-header-footer", f"--print-to-pdf={out}", str(tmp)],
        check=True, capture_output=True)


def md_titles(md: Path):
    """提取 ## 模板标题（去掉 markdown 记号）"""
    text = md.read_text(encoding="utf-8")
    return [re.sub(r"[`*]", "", m.group(1)).strip()
            for m in re.finditer(r"^## (.+)$", text, re.M)]


def template_pages(pdf: Path, titles):
    """pdftotext 扫描各模板标题所在本地页码(0-based)；找不到为 None"""
    txt = subprocess.run(["pdftotext", str(pdf), "-"],
                         capture_output=True, text=True).stdout
    starts = []
    for p in txt.split("\f")[:-1]:
        first = next((l.strip() for l in p.splitlines() if l.strip()), "")
        starts.append(re.sub(r"\s", "", first))
    locs = []
    for t in titles:
        key = re.sub(r"\s", "", t)
        locs.append(next((i for i, s in enumerate(starts) if s.startswith(key[:4])), None))
    return locs


def make_overlay(n_pages, w, h, start=1, total=None):
    """页号 overlay PDF (内存对象)：页脚居中 'N / total'"""
    if total is None:
        total = start + n_pages - 1
    buf = io.BytesIO()
    c = canvas.Canvas(buf, pagesize=(float(w), float(h)))
    c.setFont("Helvetica", 9)
    c.setFillColor(Color(0.35, 0.35, 0.35))
    for i in range(n_pages):
        c.drawCentredString(float(w) / 2, 16, f"{start + i} / {total}")
        c.showPage()
    c.save()
    buf.seek(0)
    return PdfReader(buf)


files = sorted(SRC.glob("*.md"))
if not files:
    sys.exit("未找到 md 文件")

merged = PdfWriter()
offset = 0
for md in files:
    raw = Path(tempfile.mkdtemp()) / f"{md.stem}.pdf"
    md_to_pdf(md, raw)
    reader = PdfReader(raw)
    n = len(reader.pages)
    w, h = reader.pages[0].mediabox.width, reader.pages[0].mediabox.height

    # 1) 单文件：本文件页号 "N / n"
    ov = make_overlay(n, w, h)
    for i, page in enumerate(reader.pages):
        page.merge_page(ov.pages[i])
    w1 = PdfWriter()
    w1.append(reader)
    out = DST / f"{md.stem}.pdf"
    with out.open("wb") as f:
        w1.write(f)

    # 2) 合集：追加未盖章的原始页面 + 书签
    titles = md_titles(md)
    locs = template_pages(raw, titles)
    merged.append(PdfReader(raw))
    cat = merged.add_outline_item(md.stem, offset)
    marks = 0
    for t, p in zip(titles, locs):
        if p is not None:
            merged.add_outline_item(t, offset + p, parent=cat)
            marks += 1
    offset += n
    print(f"{out.name}: {n} 页, {out.stat().st_size // 1024} KB, 书签 {marks}")

# 3) 合集连续页号 "N / total"
pages = list(merged.pages)
w, h = pages[0].mediabox.width, pages[0].mediabox.height
ov = make_overlay(len(pages), w, h)
for i, page in enumerate(pages):
    page.merge_page(ov.pages[i])
merged.add_metadata({"/Title": "ACM-XCPC 模板合集", "/Creator": "打印/md2pdf.py"})
with MERGED.open("wb") as f:
    merged.write(f)
print(f"{MERGED.name}: {len(pages)} 页, {MERGED.stat().st_size // 1024} KB")
print("完成 ->", DST)
