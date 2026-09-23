/**
 * Ihxnan 后端 — 实时扫描文件系统
 *
 * 用法:
 *   node server.js [port]       纯只读（服务器部署）
 *   node server.js --edit [port]  开启网页编辑（仅本地；写接口另限回环）
 * 默认端口 3000
 */

// ─── 可调配置：各平台比赛预设总题数 ─────────────────────────
const DEFAULT_TOTAL = {
    // 按文件夹路径前缀匹配 (从仓库根开始)
    // 越具体的规则优先
    atcoder: {
        default: 7, // ABC 通常 A-G
    },
    codeforces: {
        // 规则: 匹配文件夹名包含的关键字
        'Div.1 + Div.2': 9, // A-I
        'Div.2': 6, // A-F
        default: 7,
    },
    nowcoder: {
        牛客周赛: 6, // A-F
        牛客月赛: 6, // A-F
        牛客练习赛: 6, // A-F
        '2025牛客暑期多校训练营': 12, // 按场次不同
        default: 6,
    },
    hdu: {
        暑期联赛: 13,
        default: 10,
    },
};

// ─── 各平台题目 URL 构建规则 ──────────────────────────────
// 按 config.url 的域名分发题目链接（XCPC 现场赛与算法课程设计的 vjudge/qoj 比赛共用）
function problemUrlByHost(baseUrl, id) {
    const url = baseUrl.replace(/\/+$/, '');
    let host;
    try {
        host = new URL(url).hostname;
    } catch {
        return null;
    }
    if (host === 'qoj.ac' || host.endsWith('.qoj.ac')) return `${url}/problem/${id}`;
    if (host === 'vjudge.net' || host.endsWith('.vjudge.net')) return `${url}#problem/${id}`;
    return null;
}

const PROBLEM_URL = {
    codeforces: (baseUrl, id) => {
        const url = baseUrl.replace(/\/+$/, '');
        return `${url}/problem/${id}`;
    },
    nowcoder: (baseUrl, id) => {
        const url = baseUrl.replace(/\/+$/, '');
        return `${url}/${id}`;
    },
    atcoder: (baseUrl, id) => {
        const url = baseUrl.replace(/\/+$/, '');
        const m = url.match(/\/contests\/([^/]+)$/);
        return m ? `${url}/tasks/${m[1]}_${id.toLowerCase()}` : null;
    },
    hdu: (baseUrl, id) => {
        try {
            // 从 baseUrl 提取 cid 参数
            const urlObj = new URL(baseUrl);
            const cid = urlObj.searchParams.get('cid');
            if (!cid) return null;
            const pid = 1000 + parseInt(id, 10);
            return `https://acm.hdu.edu.cn/contest/problem?cid=${cid}&pid=${pid}`;
        } catch {
            return null;
        }
    },
    luogu: (baseUrl, id) => {
        return `https://www.luogu.com.cn/problem/${id}`;
    },
    xcpc: problemUrlByHost,
    course: problemUrlByHost,
};

/** 生成该场比赛的全部题号（字母或数字；字母题遇到 C1/C2 这类变体时展开显示） */
function generateProblemIds(platform, total, solved = []) {
    if (total == null) return null;
    const ids = [];
    const isNumeric = platform === 'hdu';
    if (isNumeric) {
        for (let i = 0; i < total; i++) {
            ids.push(String(i + 1));
        }
        return ids;
    }
    // 收集大写字母+数字的变体（C1/C2），按首字母分组并保持数字序
    const variants = new Map(); // 'C' -> ['C1', 'C2']
    for (const s of solved) {
        const m = /^([A-Z])(\d+)$/.exec(s);
        if (m) {
            if (!variants.has(m[1])) variants.set(m[1], []);
            variants.get(m[1]).push(s);
        }
    }
    for (const arr of variants.values()) {
        arr.sort((a, b) => parseInt(a.slice(1), 10) - parseInt(b.slice(1), 10));
    }
    let i = 0;
    while (ids.length < total) {
        const ch = String.fromCharCode(65 + i);
        const v = variants.get(ch);
        if (v && v.length) {
            for (const id of v) {
                if (ids.length >= total) break;
                ids.push(id);
            }
        } else {
            ids.push(ch);
        }
        i++;
    }
    return ids;
}

// ─── 以下无需修改 ────────────────────────────────────────────
const http = require('http');
const fs = require('fs');
const path = require('path');
const { spawn } = require('child_process');

const ROOT = __dirname;

/** 题目文件名校验正则：单大写字母(A)、数字1~20、或大写字母+数字（如 C1、C2、P10446） */
const PROBLEM_FILE_PATTERN = /^[A-Z]$|^(?:[1-9]|1[0-9]|20)$|^[A-Z]\d+$/;

/** 获取目录下的题目文件列表（去重，按字母排序）
 *  loose=true 时（算法课程设计：vjudge 比赛题，文件名如「A Quoit Design.cpp」）
 *  取文件名首段作为题号（A），严格模式只认标准题名。 */
function getSolved(dir, loose = false) {
    const files = fs.readdirSync(dir).filter((f) => {
        const ext = path.extname(f).toLowerCase();
        return (ext === '.cpp' || ext === '.py') && f[0] !== '.';
    });
    // 提取题号: A.cpp → A,  P2280.py → P2280，然后去重
    const seen = new Set();
    const result = [];
    for (const f of files) {
        const stem = path.basename(f, path.extname(f));
        const name = loose ? stem.split(/[. ]/, 1)[0] : stem;
        if (!PROBLEM_FILE_PATTERN.test(name)) continue; // 只认标准题名
        if (seen.has(name)) continue;
        seen.add(name);
        result.push(name);
    }
    // 字母题排前面 (A,B,C...)，数字题排后面 (P10446...)
    result.sort((a, b) => {
        const aIsLetter = /^[A-Z]$/.test(a);
        const bIsLetter = /^[A-Z]$/.test(b);
        if (aIsLetter && !bIsLetter) return -1;
        if (!aIsLetter && bIsLetter) return 1;
        return a.localeCompare(b);
    });
    return result;
}

/** 获取预设总题数 */
function getTotal(name, platform) {
    const rules = DEFAULT_TOTAL[platform];
    if (!rules) return null;
    for (const [key, total] of Object.entries(rules)) {
        if (key === 'default') continue;
        if (name.includes(key)) return total;
    }
    return rules.default || null;
}

/** 判断目录是否为比赛目录：含有题目文件或 .config.json */
function isContestDir(dirPath) {
    let entries;
    try {
        entries = fs.readdirSync(dirPath, { withFileTypes: true });
    } catch {
        return false;
    }
    for (const e of entries) {
        if (!e.isFile()) continue;
        if (e.name === '.config.json') return true;
        const ext = path.extname(e.name).toLowerCase();
        if ((ext === '.cpp' || ext === '.py') && !e.name.startsWith('.')) return true;
    }
    return false;
}

/** 构建单个比赛条目 */
function buildContest(dirPath, platform) {
    const dirName = path.basename(dirPath);
    const solved = getSolved(dirPath, platform === 'course');
    const solvedCount = solved.length;

    // 优先读取 .config.json 中的题数和链接
    let total = null;
    let url = null;
    let hasConfig = false;
    const configPath = path.join(dirPath, '.config.json');
    try {
        const configRaw = fs.readFileSync(configPath, 'utf-8');
        const config = JSON.parse(configRaw);
        hasConfig = true;
        if (config.cnt != null) total = config.cnt;
        if (config.url != null) url = config.url;
    } catch {
        // .config.json 不存在或格式错误，使用默认值
        total = getTotal(dirName, platform);
    }
    // config 存在但没 cnt 时也回退到默认值
    if (total == null) total = getTotal(dirName, platform);

    // 是否完成：通过文件数量判断
    const finished = total != null ? solvedCount >= total : false;

    // 生成所有题目列表（含未做的占位）
    const allIds = generateProblemIds(platform, total, solved);
    let allProblems = null;
    if (allIds && url && PROBLEM_URL[platform]) {
        allProblems = allIds.map((id) => ({
            id,
            solved: solved.includes(id),
            url: PROBLEM_URL[platform](url, id),
        }));
    }

    return {
        name: dirName,
        url,
        finished,
        solved,
        solvedCount,
        total,
        hasConfig,
        dir: path.relative(ROOT, dirPath),
        allProblems,
    };
}

/**
 * 扫描一个平台目录（递归，兼容分组嵌套结构）
 * 比赛目录 = 含有题目文件或 .config.json 的目录；
 * 分组目录（如 CodeForces/Div. 2、NowCoder/2026牛客暑期多校训练营）继续向下递归。
 */
function scanPlatform(platformDir, platform) {
    const base = path.join(ROOT, platformDir);
    const results = [];

    function walk(dir) {
        let entries;
        try {
            entries = fs.readdirSync(dir, { withFileTypes: true });
        } catch {
            return;
        }
        for (const entry of entries) {
            if (!entry.isDirectory()) continue;
            const dirPath = path.join(dir, entry.name);
            if (isContestDir(dirPath)) {
                results.push(buildContest(dirPath, platform));
            } else {
                walk(dirPath);
            }
        }
    }

    walk(base);

    // 排序: 未完成的排在前面，同状态按名称排序
    results.sort((a, b) => {
        if (a.finished !== b.finished) return a.finished ? 1 : -1;
        return a.name.localeCompare(b.name, 'zh-CN');
    });

    return results;
}

/**
 * 扫描「章节树」目录（LuoGu 与 算法课程设计 共用），返回扁平的章节列表。
 * 结构：base/章节/题目.cpp，题目 id 取文件名（不含扩展名，宽松命名）。
 * makeUrl(id) 生成题目在线链接（无则返回 null）。
 */
function scanChapters(baseRel, makeUrl) {
    const base = path.join(ROOT, baseRel);

    function walk(dir) {
        let entries;
        try {
            entries = fs.readdirSync(dir, { withFileTypes: true });
        } catch {
            return null;
        }

        const chapters = [];
        const files = [];

        for (const e of entries) {
            const full = path.join(dir, e.name);
            if (e.isDirectory()) {
                const sub = walk(full);
                if (sub) chapters.push(sub);
            } else if (e.isFile() && !e.name.startsWith('.')) {
                const ext = path.extname(e.name).toLowerCase();
                if (ext === '.cpp' || ext === '.py') {
                    const id = path.basename(e.name, ext);
                    files.push({ id, url: makeUrl(id) });
                }
            }
        }

        if (chapters.length === 0 && files.length === 0) return null;

        const rel = path.relative(base, dir);
        const label = rel || path.basename(dir);

        const relDir = rel ? baseRel + '/' + rel : null;
        return { label, dir: relDir, chapters, files };
    }

    function flatten(node) {
        if (!node) return [];
        // 如果节点没有自己的题目文件但有子章节，展开子章节
        if (node.files.length === 0 && node.chapters.length > 0) {
            return node.chapters.flatMap(flatten);
        }
        // 叶子节点或有文件的中间节点
        if (node.chapters.length > 0) {
            // 既有文件又有子章节 → 返回自己 + 展开子章节
            return [node, ...node.chapters.flatMap(flatten)];
        }
        return [node];
    }

    const tree = walk(base);
    return tree ? flatten(tree) : [];
}

/** 扫描 LuoGu 目录（题目链接取题号：文件名截断到第一个 '.' 或空格） */
function scanLuogu() {
    return scanChapters('LuoGu', (id) => PROBLEM_URL.luogu(null, id.split(/[. ]/, 1)[0]));
}

/** 扫描 Template 目录下的 markdown 文档 */
function scanTemplate() {
    const base = path.join(ROOT, 'Template');
    let entries;
    try {
        entries = fs.readdirSync(base, { withFileTypes: true });
    } catch {
        return [];
    }
    return entries
        .filter(
            (e) => e.isFile() && e.name.toLowerCase().endsWith('.md') && !e.name.startsWith('.'),
        )
        .sort((a, b) => a.name.localeCompare(b.name, 'zh-CN'))
        .map((e) => ({ name: e.name.replace(/\.md$/i, ''), file: e.name }));
}

/** 扫描 Downloads 目录（分发用安装包等）：列出文件 + 大小 + mtime，新→旧排序 */
function scanDownloads() {
    const base = path.join(ROOT, 'Downloads');
    let entries;
    try {
        entries = fs.readdirSync(base, { withFileTypes: true });
    } catch {
        return [];
    }
    return entries
        .filter((e) => e.isFile() && !e.name.startsWith('.'))
        .map((e) => {
            let size = 0,
                mtime = 0;
            try {
                const st = fs.statSync(path.join(base, e.name));
                size = st.size;
                mtime = st.mtimeMs;
            } catch {}
            return { name: e.name, file: e.name, size, mtime };
        })
        .sort((a, b) => b.mtime - a.mtime);
}

// ─── 复制用模板内联（参照 nvim clipboard.lua 的 Ctrl+a+Ctrl+i）───
const INCLUDE_DIR = '/usr/local/include/';

// Python 竞赛模板（Template 仓库版）
const PY_TEMPLATE_FILE = '/home/ihxnan/Github/Template/Template/ihxnan.py';

// 常见 C/C++ 标准库头：单独 #include 时视为标准库，不参与内联
const STD_HEADERS = new Set([
    'algorithm',
    'array',
    'atomic',
    'bitset',
    'cassert',
    'cctype',
    'cerrno',
    'cfenv',
    'cfloat',
    'chrono',
    'cinttypes',
    'climits',
    'clocale',
    'cmath',
    'complex',
    'condition_variable',
    'csetjmp',
    'csignal',
    'cstdarg',
    'cstdbool',
    'cstddef',
    'cstdint',
    'cstdio',
    'cstdlib',
    'cstring',
    'ctgmath',
    'ctime',
    'cuchar',
    'cwchar',
    'cwctype',
    'deque',
    'exception',
    'filesystem',
    'forward_list',
    'fstream',
    'functional',
    'future',
    'initializer_list',
    'iomanip',
    'ios',
    'iosfwd',
    'iostream',
    'istream',
    'iterator',
    'limits',
    'list',
    'locale',
    'map',
    'memory',
    'mutex',
    'new',
    'numeric',
    'optional',
    'ostream',
    'queue',
    'random',
    'ratio',
    'regex',
    'scoped_allocator',
    'set',
    'shared_mutex',
    'sstream',
    'stack',
    'stdexcept',
    'streambuf',
    'string',
    'string_view',
    'system_error',
    'thread',
    'tuple',
    'type_traits',
    'typeindex',
    'typeinfo',
    'unordered_map',
    'unordered_set',
    'utility',
    'valarray',
    'variant',
    'vector',
    'assert.h',
    'ctype.h',
    'errno.h',
    'float.h',
    'limits.h',
    'locale.h',
    'math.h',
    'setjmp.h',
    'signal.h',
    'stdarg.h',
    'stddef.h',
    'stdio.h',
    'stdlib.h',
    'string.h',
    'time.h',
    'wchar.h',
    'wctype.h',
    'complex.h',
    'fenv.h',
    'inttypes.h',
    'iso646.h',
    'stdbool.h',
    'stdint.h',
    'tgmath.h',
    'uchar.h',
]);

/** 判断 #include <name> 是否为可内联的自定义模板（位于 INCLUDE_DIR 且非标准库） */
function isCustomInclude(name) {
    if (!name || name.includes('/') || STD_HEADERS.has(name)) return false;
    return fs.existsSync(INCLUDE_DIR + name);
}

/** 读取模板文件并按行拆分；失败返回 null */
function readTemplateLines(file) {
    try {
        const lines = fs.readFileSync(file, 'utf-8').split(/\r?\n/);
        if (lines.length && lines[lines.length - 1] === '') lines.pop();
        return lines;
    } catch {
        return null;
    }
}

/**
 * 生成内联模板后的完整可提交代码：
 * - cpp: 自定义 #include <name>（/usr/local/include/ 下存在且非标准库）展开为完整源码，不递归
 * - python: from ihxnan import * 展开为 ihxnan.py 完整源码
 * 模板读取失败时保留原行；返回 { full, inlined }，无内联时 full === content
 */
function inlineTemplates(content, language) {
    const srcLines = content.split(/\r?\n/);
    const out = [];
    const inlined = [];
    let needSeparator = false;

    // 带惰性空行的插入：内联内容之后有实际代码时才补一个空行分隔
    const emit = (text) => {
        if (needSeparator && text !== '') out.push('');
        needSeparator = false;
        out.push(text);
    };

    const inlineFile = (line, file, name) => {
        const tpl = readTemplateLines(file);
        if (tpl) {
            tpl.forEach(emit);
            needSeparator = true;
            inlined.push(name);
        } else {
            emit(line); // 模板读取失败：保留原行
        }
    };

    const includePattern = /^\s*#include\s*[<"]([^>"]+)[>"]/;
    for (const line of srcLines) {
        if (language === 'python') {
            if (/^\s*from\s+ihxnan\s+import\s+\*\s*$/.test(line)) {
                inlineFile(line, PY_TEMPLATE_FILE, 'ihxnan');
            } else {
                emit(line);
            }
        } else {
            const m = line.match(includePattern);
            if (m && isCustomInclude(m[1])) {
                inlineFile(line, INCLUDE_DIR + m[1], m[1]);
            } else {
                emit(line);
            }
        }
    }

    return { full: out.join('\n'), inlined };
}

// ─── HTTP 服务 ──────────────────────────────────────────────
const EDIT_ENABLED = process.argv.slice(2).includes('--edit');
const PORT =
    parseInt(
        process.argv.slice(2).find((a) => /^\d+$/.test(a)),
        10,
    ) || 3000;

// SSE 客户端列表
const sseClients = new Set();

// ─── 响应缓存 ────────────────────────────────────────────────
let dataCache = null;
let cacheDirty = true;
function invalidateCache() {
    cacheDirty = true;
}

function sendSSE(data) {
    for (const res of sseClients) {
        try {
            res.write(`data: ${JSON.stringify(data)}\n\n`);
        } catch {}
    }
}

const MIME = {
    '.html': 'text/html; charset=utf-8',
    '.css': 'text/css; charset=utf-8',
    '.js': 'application/javascript; charset=utf-8',
    '.json': 'application/json; charset=utf-8',
    '.svg': 'image/svg+xml',
    '.png': 'image/png',
    '.ico': 'image/x-icon',
    '.md': 'text/markdown; charset=utf-8',
    '.woff2': 'font/woff2',
    '.woff': 'font/woff',
    '.ttf': 'font/ttf',
    '.pdf': 'application/pdf',
    '.txt': 'text/plain; charset=utf-8',
    '.zip': 'application/zip',
    '.7z': 'application/x-7z-compressed',
    '.rar': 'application/vnd.rar',
    '.gz': 'application/gzip',
    '.tar': 'application/x-tar',
    '.exe': 'application/vnd.microsoft.portable-executable',
    '.msi': 'application/x-msi',
};

// ─── 网页编辑（--edit）：路径/区域/大小 校验 ────────────────
const MAX_TEXT = 256 * 1024; // 文本上限 256KB
const READ_TEXT_EXTS = new Set([
    '.cpp',
    '.py',
    '.md',
    '.json',
    '.txt',
    '.in',
    '.out',
    '.html',
    '.css',
    '.js',
    '.hpp',
]);
const FORBIDDEN_SEGMENTS = new Set(['.git', '.reasonix', 'node_modules']);

/** 请求是否来自本机回环 */
function isLoopback(req) {
    const a = req.socket.remoteAddress || '';
    return a === '127.0.0.1' || a === '::1' || a === '::ffff:127.0.0.1';
}

/** 规范化相对 ROOT 的路径；非法/越狱返回 null */
function safeRel(raw) {
    if (typeof raw !== 'string' || !raw) return null;
    let dec;
    try {
        dec = decodeURIComponent(raw);
    } catch {
        return null;
    }
    const abs = path.resolve(ROOT, dec);
    if (abs !== ROOT && !abs.startsWith(ROOT + path.sep)) return null;
    const rel = path.relative(ROOT, abs);
    if (rel.startsWith('..') || path.isAbsolute(rel)) return null;
    return rel;
}

/** 可读（GET /api/file）：仓库内文本扩展名即可 */
function isReadableRel(rel) {
    if (!rel) return false;
    const segs = rel.split(/[\\/]/);
    if (segs.some((s) => FORBIDDEN_SEGMENTS.has(s))) return false;
    return READ_TEXT_EXTS.has(path.extname(rel).toLowerCase());
}

/**
 * 可写（PUT /api/file）区域白名单（与 docs/编辑功能设计.md 一致）：
 *   A. 非 Template 下的 .cpp/.py            → 题解源码
 *   B. Template/*.md（排除 Template/pdf/）   → 模板文档
 *   C. 任意 basename == .config.json         → 比赛元数据
 */
function isWritableRel(rel) {
    if (!rel) return false;
    const segs = rel.split(/[\\/]/);
    if (segs.some((s) => FORBIDDEN_SEGMENTS.has(s))) return false;
    const base = path.basename(rel);
    const ext = path.extname(base).toLowerCase();
    if (base === '.config.json') return true;
    if (rel.startsWith('Template/')) {
        if (rel.startsWith('Template/pdf/')) return false;
        return ext === '.md'; // 排除 Template/md2pdf.py 等
    }
    return ext === '.cpp' || ext === '.py';
}

/**
 * 可新建（POST /api/file）：在可写区域内，且只允许
 *   - 题解 .cpp/.py（stem 限字母数字，如 A.cpp / 10.cpp / P10446.cpp）
 *   - .config.json
 * Template/*.md 不允许新建（编辑已够，避免乱建文档）。
 */
function isCreatableRel(rel) {
    if (!isWritableRel(rel)) return false;
    const base = path.basename(rel);
    if (base === '.config.json') return true;
    return /^[A-Za-z0-9]+\.(cpp|py)$/.test(base);
}

/** 读取请求体（JSON），带大小上限 */
function readBody(req, limit) {
    return new Promise((resolve, reject) => {
        let size = 0;
        const chunks = [];
        req.on('data', (c) => {
            size += c.length;
            if (size > limit) {
                reject(new Error('请求体过大'));
                req.destroy();
                return;
            }
            chunks.push(c);
        });
        req.on('end', () => resolve(Buffer.concat(chunks)));
        req.on('error', reject);
    });
}

/** 原子写：同目录临时文件 + rename 替换 */
function atomicWrite(filePath, content) {
    const tmp = filePath + '.' + process.pid + '.tmp';
    try {
        fs.writeFileSync(tmp, content, 'utf8');
        fs.renameSync(tmp, filePath);
    } finally {
        try {
            if (fs.existsSync(tmp)) fs.unlinkSync(tmp);
        } catch {}
    }
}

const server = http.createServer((req, res) => {
    const url = new URL(req.url, `http://localhost:${PORT}`);
    const pathname = url.pathname;

    // 能力探测：编辑功能是否可用（--edit 且本机回环）
    if (pathname === '/api/capabilities') {
        res.setHeader('Access-Control-Allow-Origin', '*');
        res.setHeader('Content-Type', 'application/json; charset=utf-8');
        res.end(JSON.stringify({ edit: EDIT_ENABLED && isLoopback(req) }));
        return;
    }

    // SSE 端点
    if (pathname === '/api/events') {
        res.writeHead(200, {
            'Content-Type': 'text/event-stream',
            'Cache-Control': 'no-cache',
            Connection: 'keep-alive',
            'Access-Control-Allow-Origin': '*',
        });
        // 发送初始连接确认
        res.write(`data: ${JSON.stringify({ type: 'connected' })}\n\n`);
        sseClients.add(res);
        req.on('close', () => sseClients.delete(res));
        return;
    }

    // API 路由
    if (pathname === '/api/data') {
        res.setHeader('Access-Control-Allow-Origin', '*');
        res.setHeader('Content-Type', 'application/json; charset=utf-8');

        // 缓存命中且未过期 → 直接返回
        if (dataCache && !cacheDirty) {
            res.end(JSON.stringify(dataCache, null, 2));
            return;
        }

        try {
            const data = {
                atcoder: scanPlatform('AtCoder', 'atcoder'),
                codeforces: scanPlatform('CodeForces', 'codeforces'),
                hdu: scanPlatform('HDU', 'hdu'),
                nowcoder: scanPlatform('NowCoder', 'nowcoder'),
                xcpc: scanPlatform('XCPC', 'xcpc'),
                luogu: scanLuogu(),
                course: scanPlatform('算法课程设计', 'course'),
                template: scanTemplate(),
                downloads: scanDownloads(),
            };

            // 计算统计
            let totalContests = 0,
                finishedContests = 0,
                totalProblems = 0;
            for (const platform of ['atcoder', 'codeforces', 'hdu', 'nowcoder', 'xcpc', 'course']) {
                for (const c of data[platform]) {
                    totalContests++;
                    if (c.finished) finishedContests++;
                    totalProblems += c.solvedCount;
                }
            }
            // LuoGu 题数
            // 章节树类（LuoGu）题数
            function countChapterFiles(chapters) {
                let n = 0;
                for (const ch of chapters) {
                    n += ch.files.length;
                    if (ch.chapters) n += countChapterFiles(ch.chapters);
                }
                return n;
            }
            totalProblems += countChapterFiles(data.luogu);

            data.stats = { totalContests, finishedContests, totalProblems };

            // 写入缓存
            dataCache = data;
            cacheDirty = false;

            res.end(JSON.stringify(data, null, 2));
        } catch (err) {
            res.statusCode = 500;
            res.end(JSON.stringify({ error: err.message }));
        }
        return;
    }

    // 代码查看 API
    if (pathname === '/api/code') {
        res.setHeader('Access-Control-Allow-Origin', '*');
        res.setHeader('Content-Type', 'application/json; charset=utf-8');

        const dir = url.searchParams.get('dir');
        const problem = url.searchParams.get('problem');

        if (!dir || !problem) {
            res.statusCode = 400;
            res.end(JSON.stringify({ error: '缺少 dir 或 problem 参数' }));
            return;
        }

        // 安全检查：路径必须在 ROOT 下，且只允许 .cpp / .py
        const dirPath = path.resolve(ROOT, dir);
        if (!dirPath.startsWith(ROOT + path.sep) && dirPath !== ROOT) {
            res.statusCode = 403;
            res.end(JSON.stringify({ error: '禁止访问' }));
            return;
        }

        let filePath = null;
        for (const ext of ['.cpp', '.py']) {
            const candidate = path.join(dirPath, problem + ext);
            if (fs.existsSync(candidate)) {
                filePath = candidate;
                break;
            }
        }

        // 回退：宽松命名（如「A Quoit Design.cpp」，题号由首段识别为 A）按题号前缀匹配；
        // 取最短匹配，避免「C 过河卒.cpp」被「C 过河卒二.cpp」抢走。
        if (!filePath) {
            try {
                const esc = problem.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
                const re = new RegExp('^' + esc + '(?![A-Za-z0-9])[^/]*\\.(cpp|py)$', 'i');
                const hits = fs.readdirSync(dirPath).filter((f) => re.test(f));
                hits.sort((a, b) => a.length - b.length || a.localeCompare(b));
                if (hits.length) filePath = path.join(dirPath, hits[0]);
            } catch {}
        }

        if (!filePath) {
            res.statusCode = 404;
            res.end(JSON.stringify({ error: '文件未找到' }));
            return;
        }

        try {
            const content = fs.readFileSync(filePath, 'utf-8');
            const ext = path.extname(filePath).toLowerCase();
            const language = ext === '.py' ? 'python' : 'cpp';
            const { full, inlined } = inlineTemplates(content, language);
            const rel = path.relative(ROOT, filePath);
            res.end(
                JSON.stringify({
                    content,
                    full,
                    inlined,
                    language,
                    file: path.basename(filePath),
                    mtime: fs.statSync(filePath).mtimeMs,
                    editable: EDIT_ENABLED && isLoopback(req) && isWritableRel(rel),
                }),
            );
        } catch (err) {
            res.statusCode = 500;
            res.end(JSON.stringify({ error: err.message }));
        }
        return;
    }

    // ── 通用文本读取（GET /api/file?path=相对路径）──
    if (pathname === '/api/file' && req.method === 'GET') {
        res.setHeader('Access-Control-Allow-Origin', '*');
        res.setHeader('Content-Type', 'application/json; charset=utf-8');
        const rel = safeRel(url.searchParams.get('path'));
        if (!rel || !isReadableRel(rel)) {
            res.statusCode = 403;
            res.end(JSON.stringify({ error: '禁止访问' }));
            return;
        }
        const filePath = path.join(ROOT, rel);
        try {
            const stat = fs.statSync(filePath);
            if (!stat.isFile()) throw new Error('不是文件');
            if (stat.size > MAX_TEXT) {
                res.statusCode = 413;
                res.end(JSON.stringify({ error: '文件过大' }));
                return;
            }
            const content = fs.readFileSync(filePath, 'utf8');
            if (content.includes('\u0000')) {
                res.statusCode = 415;
                res.end(JSON.stringify({ error: '二进制文件' }));
                return;
            }
            res.end(
                JSON.stringify({
                    content,
                    mtime: stat.mtimeMs,
                    writable: EDIT_ENABLED && isLoopback(req) && isWritableRel(rel),
                }),
            );
        } catch (err) {
            res.statusCode = 404;
            res.end(JSON.stringify({ error: '文件未找到' }));
        }
        return;
    }

    // ── 写入文件（PUT /api/file，需 --edit 且本机回环）──
    if (pathname === '/api/file' && req.method === 'PUT') {
        res.setHeader('Access-Control-Allow-Origin', '*');
        res.setHeader('Content-Type', 'application/json; charset=utf-8');
        (async () => {
            if (!EDIT_ENABLED) {
                res.statusCode = 403;
                res.end(JSON.stringify({ error: '编辑未开启（需 node server.js --edit）' }));
                return;
            }
            if (!isLoopback(req)) {
                res.statusCode = 403;
                res.end(JSON.stringify({ error: '仅限本机编辑' }));
                return;
            }

            let payload;
            try {
                const raw = await readBody(req, MAX_TEXT + 4096);
                payload = JSON.parse(raw.toString('utf8'));
            } catch {
                res.statusCode = 400;
                res.end(JSON.stringify({ error: '请求体非法' }));
                return;
            }
            const { path: relRaw, content, baseMtime } = payload || {};
            if (typeof content !== 'string') {
                res.statusCode = 400;
                res.end(JSON.stringify({ error: '缺少 content' }));
                return;
            }
            const rel = safeRel(relRaw);
            if (!rel) {
                res.statusCode = 403;
                res.end(JSON.stringify({ error: '禁止访问' }));
                return;
            }
            if (!isWritableRel(rel)) {
                res.statusCode = 403;
                res.end(JSON.stringify({ error: '该文件不在可编辑区域' }));
                return;
            }
            const filePath = path.join(ROOT, rel);
            if (!fs.existsSync(filePath)) {
                res.statusCode = 404;
                res.end(JSON.stringify({ error: '文件不存在（暂不支持新建）' }));
                return;
            }
            if (Buffer.byteLength(content, 'utf8') > MAX_TEXT) {
                res.statusCode = 413;
                res.end(JSON.stringify({ error: '内容过大' }));
                return;
            }
            if (content.includes('\u0000')) {
                res.statusCode = 415;
                res.end(JSON.stringify({ error: '不支持二进制内容' }));
                return;
            }
            if (path.basename(rel) === '.config.json') {
                try {
                    JSON.parse(content);
                } catch {
                    res.statusCode = 400;
                    res.end(JSON.stringify({ error: '.config.json 内容不是合法 JSON' }));
                    return;
                }
            }

            // 乐观锁：baseMtime 与磁盘不符 → 409（baseMtime 为 null 表示用户确认强制覆盖）
            const statNow = fs.statSync(filePath);
            if (baseMtime != null && Math.abs(statNow.mtimeMs - Number(baseMtime)) > 0.5) {
                res.statusCode = 409;
                res.end(JSON.stringify({ error: 'CONFLICT', mtime: statNow.mtimeMs }));
                return;
            }

            try {
                atomicWrite(filePath, content);
                invalidateCache();
                res.end(JSON.stringify({ ok: true, mtime: fs.statSync(filePath).mtimeMs }));
            } catch (err) {
                res.statusCode = 500;
                res.end(JSON.stringify({ error: '写入失败: ' + err.message }));
            }
        })();
        return;
    }

    // ── 新建文件（POST /api/file，需 --edit 且本机回环）──
    if (pathname === '/api/file' && req.method === 'POST') {
        res.setHeader('Access-Control-Allow-Origin', '*');
        res.setHeader('Content-Type', 'application/json; charset=utf-8');
        (async () => {
            if (!EDIT_ENABLED) {
                res.statusCode = 403;
                res.end(JSON.stringify({ error: '编辑未开启（需 node server.js --edit）' }));
                return;
            }
            if (!isLoopback(req)) {
                res.statusCode = 403;
                res.end(JSON.stringify({ error: '仅限本机编辑' }));
                return;
            }
            let payload;
            try {
                const raw = await readBody(req, MAX_TEXT + 4096);
                payload = JSON.parse(raw.toString('utf8'));
            } catch {
                res.statusCode = 400;
                res.end(JSON.stringify({ error: '请求体非法' }));
                return;
            }
            const { path: relRaw, content } = payload || {};
            if (typeof content !== 'string') {
                res.statusCode = 400;
                res.end(JSON.stringify({ error: '缺少 content' }));
                return;
            }
            const rel = safeRel(relRaw);
            if (!rel || !isCreatableRel(rel)) {
                res.statusCode = 403;
                res.end(JSON.stringify({ error: '该路径不允许新建' }));
                return;
            }
            const filePath = path.join(ROOT, rel);
            if (fs.existsSync(filePath)) {
                res.statusCode = 409;
                res.end(JSON.stringify({ error: 'EXISTS', path: rel }));
                return;
            }
            if (!fs.existsSync(path.dirname(filePath))) {
                res.statusCode = 404;
                res.end(JSON.stringify({ error: '目标目录不存在' }));
                return;
            }
            if (Buffer.byteLength(content, 'utf8') > MAX_TEXT) {
                res.statusCode = 413;
                res.end(JSON.stringify({ error: '内容过大' }));
                return;
            }
            if (content.includes('\u0000')) {
                res.statusCode = 415;
                res.end(JSON.stringify({ error: '不支持二进制内容' }));
                return;
            }
            if (path.basename(rel) === '.config.json') {
                try {
                    JSON.parse(content);
                } catch {
                    res.statusCode = 400;
                    res.end(JSON.stringify({ error: '.config.json 内容不是合法 JSON' }));
                    return;
                }
            }
            try {
                atomicWrite(filePath, content);
                invalidateCache();
                res.end(
                    JSON.stringify({
                        ok: true,
                        created: true,
                        mtime: fs.statSync(filePath).mtimeMs,
                    }),
                );
            } catch (err) {
                res.statusCode = 500;
                res.end(JSON.stringify({ error: '创建失败: ' + err.message }));
            }
        })();
        return;
    }

    // 静态文件（解码 URI；禁止路径逃逸出仓库根目录）
    let decodedPath;
    try {
        decodedPath = decodeURIComponent(pathname);
    } catch {
        res.statusCode = 400;
        res.end('Bad Request');
        return;
    }
    const filePath = path.join(ROOT, decodedPath === '/' ? 'index.html' : decodedPath);
    if (filePath !== ROOT && !filePath.startsWith(ROOT + path.sep)) {
        res.statusCode = 403;
        res.end('Forbidden');
        return;
    }
    const ext = path.extname(filePath);

    // 流式返回 + Range 支持（大文件如 Downloads/*.exe 可断点续传/边下边看）
    fs.stat(filePath, (err, st) => {
        if (err || !st.isFile()) {
            res.statusCode = 404;
            res.end('Not Found');
            return;
        }
        res.setHeader('Content-Type', MIME[ext] || 'application/octet-stream');
        res.setHeader('Accept-Ranges', 'bytes');

        let start = 0;
        let end = st.size - 1;
        const range = req.headers.range;
        if (range) {
            const m = /^bytes=(\d*)-(\d*)$/.exec(String(range).trim());
            if (m) {
                const [, from, to] = m;
                if (from === '' && to !== '') {
                    start = Math.max(0, st.size - Number(to)); // bytes=-N（末尾 N 字节）
                } else if (from !== '') {
                    start = Number(from);
                    if (to !== '') end = Math.min(Number(to), st.size - 1);
                }
                if (
                    !Number.isFinite(start) ||
                    !Number.isFinite(end) ||
                    start > end ||
                    start >= st.size
                ) {
                    res.statusCode = 416;
                    res.setHeader('Content-Range', `bytes */${st.size}`);
                    res.end();
                    return;
                }
                res.statusCode = 206;
                res.setHeader('Content-Range', `bytes ${start}-${end}/${st.size}`);
            }
        }
        res.setHeader('Content-Length', String(end - start + 1));
        if (req.method === 'HEAD' || st.size === 0) {
            res.end();
            return;
        }
        const stream = fs.createReadStream(filePath, { start, end });
        stream.on('error', () => {
            try {
                res.destroy();
            } catch {}
        });
        // 客户端提前断开（取消下载 / 断点续传中途重连）时释放 fd
        res.on('close', () => stream.destroy());
        stream.pipe(res);
    });
});

server.listen(PORT, '0.0.0.0', () => {
    console.log(`✓ Ihxnan 面板已启动: http://0.0.0.0:${PORT}`);
    console.log(`  API: http://0.0.0.0:${PORT}/api/data`);
    console.log('  监听文件变化中，修改后自动重启…');
});

// ─── 文件监听 ────────────────────────────────────────────────
let restartTimer;
function watchDir(dir) {
    try {
        fs.watch(dir, { recursive: true }, (event, filename) => {
            if (!filename) return;
            const ext = path.extname(filename).toLowerCase();
            // Downloads 是分发目录：扩展名不在白名单内，但任何增删改都要刷新下载列表
            const inDownloads =
                filename === 'Downloads' ||
                filename.startsWith('Downloads/') ||
                filename.startsWith('Downloads' + path.sep);
            if (
                !inDownloads &&
                !['.js', '.css', '.json', '.html', '.cpp', '.py', '.md'].includes(ext)
            )
                return;
            if (filename.includes('node_modules')) return;
            // 工具状态与 git 内部变化不代表仓库内容变化，监听它们只会让页面被无关写入反复刷新
            // （.reasonix/ 下每次工具调用都会写 snapshot.json，而 .json 恰好在白名单里）
            const rel = filename.split(path.sep).join('/');
            if (
                rel === '.git' ||
                rel.startsWith('.git/') ||
                rel === '.reasonix' ||
                rel.startsWith('.reasonix/')
            )
                return;

            clearTimeout(restartTimer);
            restartTimer = setTimeout(() => {
                // server.js 自身变化 → 重启进程（其它 .js 是浏览器代码 app.js，不重启）
                if (filename === 'server.js') {
                    console.log(`\n🔄 server.js 已修改，正在自动重启…\n`);
                    sendSSE({ type: 'server_restart' });
                    const child = spawn(process.argv[0], process.argv.slice(1), {
                        stdio: 'inherit',
                        detached: false,
                    });
                    server.close(() => process.exit());
                    setTimeout(() => process.exit(), 1000);
                    return;
                }
                // 其他文件变化 → 标记缓存过期 + SSE 通知前端重新拉取数据
                invalidateCache();
                console.log(`  📡 检测到变化: ${filename}`);
                sendSSE({ type: 'reload' });
            }, 300);
        });
    } catch {
        // recursive 在某些系统上不支持，忽略
    }
}
watchDir(ROOT);
