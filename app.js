
            let lastData = null;

            async function loadData() {
                try {
                    // 能力探测与数据并行发起：首屏只需一次渲染就能带上正确的 EDITABLE，
                    // 省掉 --edit 模式下原本的第二次 /api/data + 全量 refreshData 重渲染
                    const [res, cap] = await Promise.all([
                        fetch('/api/data'),
                        fetch('/api/capabilities').then((r) => r.json()).catch(() => null),
                    ]);
                    if (!res.ok) throw new Error('HTTP ' + res.status);
                    EDITABLE = !!(cap && cap.edit);
                    const data = await res.json();
                    lastData = data;
                    render(data);
                    if (EDITABLE) showEditBtnIfNeeded();
                } catch (err) {
                    document.getElementById('loading').style.display = 'none';
                    document.getElementById('error').style.display = 'block';
                    console.error(err);
                }
                openFromUrl();
            }

            // ── 分享链接：?dir=…&problem=… 直达某题的代码预览 ──
            function findProblemUrl(dir, problem) {
                if (!lastData) return null;
                for (const key of ['atcoder', 'codeforces', 'nowcoder', 'hdu', 'xcpc', 'course']) {
                    for (const c of lastData[key] || []) {
                        if (c.dir !== dir || !c.allProblems) continue;
                        const p = c.allProblems.find((x) => x.id === problem);
                        if (p && p.url) return p.url;
                    }
                }
                const walk = (chapters) => {
                    for (const ch of chapters || []) {
                        if (ch.dir === dir && Array.isArray(ch.files)) {
                            const f = ch.files.find((x) => (x.id || x) === problem);
                            if (f && f.url) return f.url;
                        }
                        const sub = walk(ch.chapters);
                        if (sub) return sub;
                    }
                    return null;
                };
                return walk(lastData.luogu);
            }

            // ── 分享链接：?contest=… 直达比赛详情页；?dir=…&problem=… 直达某题代码预览（可并列）──
            function openFromUrl() {
                const params = new URLSearchParams(location.search);
                const contest = params.get('contest');
                if (contest) {
                    const c = findContestByDir(contest);
                    if (c) showContest(c);
                }
                const dir = params.get('dir');
                const problem = params.get('problem');
                if (dir && problem) showCode(dir, problem, findProblemUrl(dir, problem));
            }

            // ── 报头统计 + 总进度条 ──
            let firstRender = true;
            function applyStats(data) {
                const s = data.stats;
                let known = s.totalProblems;
                for (const key of ['atcoder', 'codeforces', 'nowcoder', 'hdu', 'xcpc', 'course']) {
                    for (const c of data[key] || []) {
                        if (c.total != null) known += Math.max(0, c.total - c.solvedCount);
                    }
                }
                const pct = known > 0 ? Math.min(100, Math.round((s.totalProblems / known) * 100)) : 0;
                document.getElementById('stats').innerHTML =
                    `<div class="stat"><span class="stat-num" data-v="${s.totalContests}">0</span><span class="stat-label">场比赛</span></div>` +
                    `<div class="stat"><span class="stat-num" data-v="${s.finishedContests}">0</span><span class="stat-label">场补完</span></div>` +
                    `<div class="stat"><span class="stat-num" data-v="${s.totalProblems}">0</span><span class="stat-label">道已解决</span></div>` +
                    `<div class="stat"><span class="stat-num" data-v="${pct}" data-suffix="%">0%</span><span class="stat-label">总进度</span></div>`;
                document.getElementById('progressFill').style.width = pct + '%';
                if (firstRender) {
                    firstRender = false;
                    animateStats();
                } else {
                    finalizeStats();
                }
            }
            function animateStats() {
                const nums = [...document.querySelectorAll('#stats .stat-num')];
                const t0 = performance.now();
                const DUR = 750;
                function tick(now) {
                    const t = Math.min(1, (now - t0) / DUR);
                    const e = 1 - Math.pow(1 - t, 3);
                    nums.forEach((el) => {
                        el.textContent = Math.round(+el.dataset.v * e) + (el.dataset.suffix || '');
                    });
                    if (t < 1) requestAnimationFrame(tick);
                }
                requestAnimationFrame(tick);
            }
            function finalizeStats() {
                document.querySelectorAll('#stats .stat-num').forEach((el) => {
                    el.textContent = el.dataset.v + (el.dataset.suffix || '');
                });
            }

            // ── 导航题数徽标 ──
            function renderNav(data) {
                const counts = {};
                for (const key of ['atcoder', 'codeforces', 'nowcoder', 'hdu', 'xcpc', 'course']) {
                    counts[key] = (data[key] || []).reduce((n, c) => n + c.solvedCount, 0);
                }
                const cntLu = (chapters) =>
                    (chapters || []).reduce((n, ch) => n + (ch.files ? ch.files.length : 0) + cntLu(ch.chapters), 0);
                counts.luogu = cntLu(data.luogu);
                counts.resources = (data.template || []).length + (data.downloads || []).length;
                for (const key of Object.keys(counts)) {
                    const el = document.getElementById('navcount-' + key);
                    if (el) el.textContent = counts[key];
                }
                updateNavOverflow();
            }

            // ── 导航高亮当前板块 ──
            let navSpyReady = false;
            function setupNavSpy() {
                if (navSpyReady) return;
                navSpyReady = true;
                const links = [...document.querySelectorAll('.page-nav a')];
                const obs = new IntersectionObserver(
                    (entries) => {
                        entries.forEach((e) => {
                            if (!e.isIntersecting) return;
                            links.forEach((l) => l.classList.toggle('active', l.hash === '#' + e.target.id));
                        });
                    },
                    { rootMargin: '-25% 0px -65% 0px' }
                );
                document.querySelectorAll('#content section').forEach((sec) => obs.observe(sec));
            }

            // ── 筛选（本地过滤比赛名 / 题号 / 章节名）──
            const filterInput = document.getElementById('filter');
            let filterTimer = null;
            filterInput.addEventListener('input', () => {
                clearTimeout(filterTimer);
                filterTimer = setTimeout(applyFilter, 120);
            });

            function applyFilter() {
                const q = filterInput.value.trim().toLowerCase();
                document.body.classList.toggle('filtering', !!q);

                document.querySelectorAll('#content .contest').forEach((card) => {
                    const nameEl = card.querySelector('.name');
                    const name = (nameEl ? nameEl.textContent : '').toLowerCase();
                    const chips = [...card.querySelectorAll('.prob')].map((p) => p.textContent.toLowerCase());
                    card.style.display = !q || name.includes(q) || chips.some((c) => c.includes(q)) ? '' : 'none';
                });
                document.querySelectorAll('.platform-group').forEach((g) => {
                    const any = [...g.querySelectorAll('.contest')].some((c) => c.style.display !== 'none');
                    g.style.display = any ? '' : 'none';
                });

                // LuoGu 章节：子章节先处理（倒序），父章节连同可见子章节一起判定
                const chapters = [...document.querySelectorAll('.luogu-section .chapter')];
                for (let i = chapters.length - 1; i >= 0; i--) {
                    const ch = chapters[i];
                    const labelEl = ch.querySelector(':scope > .coll-head h3, :scope > h3');
                    const label = (labelEl ? labelEl.textContent : '').toLowerCase();
                    const ids = [...ch.querySelectorAll(':scope > .coll-inner ol li, :scope > ol li')].map((li) =>
                        li.textContent.toLowerCase()
                    );
                    const selfHit = !q || label.includes(q) || ids.some((t) => t.includes(q));
                    const subHit = [...ch.querySelectorAll(':scope > .coll-inner .sub-chapter, :scope > .sub-chapter')].some(
                        (s) => s.style.display !== 'none'
                    );
                    ch.style.display = selfHit || subHit ? '' : 'none';
                }

                document.querySelectorAll('#section-resources .template-item').forEach((item) => {
                    const nEl = item.querySelector('.doc-name');
                    const n = (nEl ? nEl.textContent : '').toLowerCase();
                    item.style.display = !q || n.includes(q) ? '' : 'none';
                });

                document.querySelectorAll('#section-resources .download-item').forEach((item) => {
                    const nEl = item.querySelector('.doc-name');
                    const n = (nEl ? nEl.textContent : '').toLowerCase();
                    item.style.display = !q || n.includes(q) ? '' : 'none';
                });

                let anyVisible = false;
                ['atcoder', 'codeforces', 'nowcoder', 'hdu', 'xcpc', 'luogu', 'course', 'resources'].forEach((k) => {
                    const sec = document.getElementById('section-' + k);
                    if (!sec) return;
                    // 资源区：模板文档 / 文件下载 两个子组各自判定，都空了才整块收起
                    if (k === 'resources') {
                        let any = false;
                        sec.querySelectorAll('.res-group').forEach((group) => {
                            const items = [...group.querySelectorAll('.template-item, .download-item')];
                            const vis = items.length > 0 && items.some((el) => el.style.display !== 'none');
                            group.style.display = vis ? '' : 'none';
                            if (vis) any = true;
                        });
                        sec.style.display = any ? '' : 'none';
                        if (any) anyVisible = true;
                        return;
                    }
                    const sel = k === 'luogu' ? '.chapter' : '.contest';
                    const any = [...sec.querySelectorAll(sel)].some((el) => el.style.display !== 'none');
                    sec.style.display = any ? '' : 'none';
                    if (any) anyVisible = true;
                });
                document.getElementById('noResult').style.display = anyVisible ? 'none' : '';
            }

            function render(data) {
                applyStats(data);
                renderNav(data);

                // 渲染各平台比赛卡片
                ['atcoder', 'codeforces', 'nowcoder', 'hdu', 'xcpc', 'course'].forEach((key) => {
                    const grid = document.getElementById('grid-' + key);
                    const list = data[key] || [];
                    renderContestList(grid, list);
                });

                // 渲染 LuoGu（章节树）
                renderChapterTree('luogu-content', data.luogu, 'luogu');

                // 渲染资源区（模板文档 + 文件下载）
                renderResources(data);

                // 切换显示
                document.getElementById('loading').style.display = 'none';
                document.getElementById('content').style.display = 'block';
                setupNavSpy();
                applyFilter();
            }

            // ── 折叠状态（localStorage 持久化，项数多时默认收起）──
            const COLLAPSE_AT = 9;
            function readCollapse(key, count) {
                try {
                    const v = localStorage.getItem('ui.collapse.' + key);
                    if (v == null) return count >= COLLAPSE_AT;
                    return v === '1';
                } catch {
                    return count >= COLLAPSE_AT;
                }
            }
            function writeCollapse(key, collapsed) {
                try {
                    localStorage.setItem('ui.collapse.' + key, collapsed ? '1' : '0');
                } catch {}
            }

            // 按平台下第一级子目录分组渲染（如 CodeForces 下 Div. 2 / Div. 3 / Educational 分开显示）
            function renderContestList(container, list) {
                if (list.length === 0) {
                    container.innerHTML = '<div class="empty">暂无数据</div>';
                    return;
                }
                // 先收集分组（保持组内原顺序）
                const groups = new Map(); // key -> { name, items }
                for (const c of list) {
                    const parts = (c.dir || '').split('/');
                    const name = parts.length >= 3 ? parts[1] : null;
                    const key = name || '\u0000'; // 无分组统一放最后
                    if (!groups.has(key)) groups.set(key, { name, items: [] });
                    groups.get(key).items.push(c);
                }
                // 有标题的分组按名称排序，无分组的排最后
                const entries = [...groups.entries()].sort((a, b) => {
                    if (a[1].name === null) return 1;
                    if (b[1].name === null) return -1;
                    return a[1].name.localeCompare(b[1].name, 'zh-CN');
                });
                const platform = (container.id || '').replace(/^grid-/, '');
                entries.forEach(([, g]) => {
                    if (g.name) {
                        const groupEl = document.createElement('div');
                        groupEl.className = 'platform-group';

                        // 折叠头：标题 + 项数徽标 + 箭头
                        const stateKey = platform + '/' + g.name;
                        if (readCollapse(stateKey, g.items.length)) groupEl.classList.add('is-collapsed');
                        const head = document.createElement('div');
                        head.className = 'coll-head';
                        const h = document.createElement('h4');
                        h.className = 'group-title';
                        h.textContent = g.name;
                        const count = document.createElement('span');
                        count.className = 'coll-count';
                        count.textContent = g.items.length + ' 场';
                        const chev = document.createElement('span');
                        chev.className = 'coll-chevron';
                        chev.textContent = '▾';
                        head.appendChild(h);
                        head.appendChild(count);
                        head.appendChild(chev);
                        head.addEventListener('click', () => {
                            const now = groupEl.classList.toggle('is-collapsed');
                            writeCollapse(stateKey, now);
                        });

                        // 可折叠的卡片容器
                        const subGrid = document.createElement('div');
                        subGrid.className = 'contest-grid';
                        const inner = document.createElement('div');
                        inner.className = 'coll-inner';
                        inner.appendChild(subGrid);
                        const coll = document.createElement('div');
                        coll.className = 'collapsible';
                        coll.appendChild(inner);

                        groupEl.appendChild(head);
                        groupEl.appendChild(coll);
                        container.appendChild(groupEl);
                        g.items.forEach((c) => renderContest(subGrid, c));
                    } else {
                        g.items.forEach((c) => renderContest(container, c));
                    }
                });
            }

            function renderContest(container, c) {
                const div = document.createElement('div');
                div.className = 'contest' + (c.dir ? ' clickable' : '') + (c.finished ? ' is-done' : ' is-ongoing');

                // 状态圆点
                const dot = document.createElement('div');
                dot.className = 'status ' + (c.finished ? 'done' : 'ongoing');

                // 名称
                const name = document.createElement('div');
                name.className = 'name';
                name.textContent = c.name;

                // 题目列表（全部：已做 + 未做占位）
                const solved = document.createElement('div');
                solved.className = 'solved';
                const problems = c.allProblems || c.solved.map(id => ({ id, solved: true, url: null }));
                problems.forEach((p) => {
                    const span = document.createElement('span');
                    span.className = 'prob ' + (p.solved ? 'solved' : 'unsolved');
                    span.textContent = p.id;
                    if (p.solved && c.dir) {
                        // 已做题目 → 点击查看代码（模态框）
                        span.title = '查看代码';
                        span.addEventListener('click', (e) => {
                            e.stopPropagation();
                            showCode(c.dir, p.id, p.url);
                        });
                    } else if (p.url) {
                        // 未做题目 → 跳转到题目页面
                        span.title = '待补题 — 打开题目页面';
                        span.addEventListener('click', (e) => {
                            e.stopPropagation();
                            window.open(p.url, '_blank');
                        });
                    } else {
                        span.title = '待补题';
                        span.style.cursor = 'default';
                    }
                    // 未解决题：可网页新建题解（hover 出 + 角标）
                    if (!p.solved && EDITABLE && c.dir) {
                        span.classList.add('addable');
                        const plus = document.createElement('span');
                        plus.className = 'prob-add';
                        plus.title = '新建题解 ' + p.id + '.cpp';
                        plus.textContent = '+';
                        plus.addEventListener('click', (e) => {
                            e.stopPropagation();
                            openMk(c, p);
                        });
                        span.appendChild(plus);
                    }
                    solved.appendChild(span);
                });
                const cnt = document.createElement('span');
                cnt.className = 'count' + (c.finished ? ' done' : '');
                if (c.total != null) {
                    cnt.textContent = `${c.solvedCount}/${c.total}`;
                } else {
                    cnt.textContent = c.solvedCount + '题';
                }
                solved.appendChild(cnt);

                // 完成标签
                const tag = document.createElement('div');
                tag.className = 'finish-tag ' + (c.finished ? 'complete' : 'incomplete');
                tag.textContent = c.finished ? '✓ 已补完' : '待补题';

                div.appendChild(dot);
                div.appendChild(name);
                div.appendChild(solved);
                div.appendChild(tag);

                // 原比赛链接（新标签打开原站）；无 .config.json 时退化为不可点的提示标记
                if (c.url) {
                    const ext = document.createElement('a');
                    ext.className = 'ext-link';
                    ext.href = c.url;
                    ext.target = '_blank';
                    ext.rel = 'noopener noreferrer';
                    ext.title = '在新标签页打开原比赛页面';
                    ext.textContent = '↗';
                    ext.addEventListener('click', (e) => e.stopPropagation());
                    div.appendChild(ext);
                } else if (!c.hasConfig) {
                    const missing = document.createElement('span');
                    missing.className = 'no-config-tag';
                    missing.title = '未配置比赛链接（.config.json 里没有 url）';
                    missing.textContent = '!';
                    div.appendChild(missing);
                } else {
                    // 占位保持对齐：有 config 但无 URL 时放一个不可见的占位符
                    const placeholder = document.createElement('span');
                    placeholder.style.cssText = 'display:inline-block;width:1.2rem;';
                    div.appendChild(placeholder);
                }

                // 比赛详情页：本页无刷新打开小窗（URL 同步为 ?contest=…）；href 保留，右键复制 / Ctrl+点击仍可新标签打开
                if (c.dir) {
                    const detail = document.createElement('a');
                    detail.className = 'detail-link';
                    detail.href = '?contest=' + encodeURIComponent(c.dir);   // 相对链接：只替换 query，保留当前路径
                    detail.title = '在本页查看比赛详情（右键可复制链接）';
                    detail.textContent = '详情';
                    detail.addEventListener('click', (e) => {
                        // 无论是否按修饰键都不能冒泡到整卡：否则 Ctrl/Cmd+点击会「既开新标签又开小窗」
                        e.stopPropagation();
                        // 修饰键点击交回浏览器原生行为（新标签打开深链），只有普通左键才拦截为本页开窗
                        if (e.metaKey || e.ctrlKey || e.shiftKey || e.altKey) return;
                        e.preventDefault();
                        showContest(c);
                    });
                    div.appendChild(detail);
                }

                // 比赛设置入口：有比赛目录即显示（无 .config.json 时进入「新建」模式）
                if (EDITABLE && c.dir) {
                    const gear = document.createElement('button');
                    gear.type = 'button';
                    gear.className = 'cfg-gear';
                    gear.title = c.hasConfig ? '编辑比赛设置 (.config.json)' : '新建比赛设置 (.config.json)';
                    gear.textContent = '⚙';
                    gear.addEventListener('click', (e) => {
                        e.stopPropagation();
                        openCfg(c);
                    });
                    div.appendChild(gear);
                }

                // 整个卡片可点击 → 打开比赛信息小窗（原比赛链接收进小窗里）
                if (c.dir) {
                    div.addEventListener('click', () => showContest(c));
                }

                container.appendChild(div);
            }

            function renderLuoguChapter(ch, parent, depth = 0, prefix = 'luogu') {
                const div = document.createElement('div');
                div.className = depth > 0 ? 'sub-chapter chapter' : 'chapter';

                const hasFiles = ch.files && ch.files.length > 0;
                let contentParent = div;

                if (ch.label) {
                    if (hasFiles) {
                        // 可折叠章节：标题 + 题数徽标 + 箭头
                        const stateKey = prefix + '/' + ch.label;
                        if (readCollapse(stateKey, ch.files.length)) div.classList.add('is-collapsed');
                        const head = document.createElement('div');
                        head.className = 'coll-head';
                        const h3 = document.createElement('h3');
                        h3.textContent = ch.label;
                        const count = document.createElement('span');
                        count.className = 'coll-count';
                        count.textContent = ch.files.length + ' 题';
                        const chev = document.createElement('span');
                        chev.className = 'coll-chevron';
                        chev.textContent = '▾';
                        head.appendChild(h3);
                        head.appendChild(count);
                        head.appendChild(chev);
                        head.addEventListener('click', () => {
                            const now = div.classList.toggle('is-collapsed');
                            writeCollapse(stateKey, now);
                        });
                        div.appendChild(head);

                        const inner = document.createElement('div');
                        inner.className = 'coll-inner';
                        const coll = document.createElement('div');
                        coll.className = 'collapsible';
                        coll.appendChild(inner);
                        div.appendChild(coll);
                        contentParent = inner;
                    } else {
                        const h3 = document.createElement('h3');
                        h3.textContent = ch.label;
                        div.appendChild(h3);
                    }
                }

                if (hasFiles) {
                    const ol = document.createElement('ol');
                    ch.files.forEach((f) => {
                        const id = f.id || f;
                        const li = document.createElement('li');
                        li.textContent = id;
                        if (ch.dir) {
                            li.title = '查看代码';
                            li.style.cursor = 'pointer';
                            li.addEventListener('click', () => showCode(ch.dir, id, f.url || null));
                        }
                        ol.appendChild(li);
                    });
                    contentParent.appendChild(ol);
                }

                if (ch.chapters) {
                    ch.chapters.forEach((sub) => renderLuoguChapter(sub, contentParent, depth + 1, prefix));
                }

                parent.appendChild(div);
            }

            // 渲染一棵章节树到指定容器（LuoGu / 算法课程设计 共用）
            function renderChapterTree(containerId, chapters, prefix) {
                const box = document.getElementById(containerId);
                if (!box) return;
                box.innerHTML = '';
                if (!chapters || chapters.length === 0) {
                    box.innerHTML = '<div class="empty">暂无数据</div>';
                    return;
                }
                chapters.forEach((ch) => renderLuoguChapter(ch, box, 0, prefix));
            }

            // ── 代码查看 ──
            // 复制按钮：复制内联模板后的完整可提交代码（参照 nvim clipboard.lua）
            // 本脚本执行早于模态框 DOM，按钮需在首次使用时惰性初始化
            let copyBtn = null;

            // ── 分享链接（可直接访问 / 复制）──
            // 把当前打开的内容映射到 URL：?contest=<比赛目录>&dir=<目录>&problem=<题号>，逐层可选。
            // 比赛小窗 → contest；代码小窗 → dir + problem（两者同时打开时并列，刷新可还原两层）。
            // 注意 ctDir 在后文（比赛小窗区块）声明，此函数只在页面运行期被调用，不构成 TDZ 访问。
            let codeShare = null;      // { dir, problem } —— 代码小窗当前的分享目标

            function writeShareUrl() {
                const params = new URLSearchParams();
                if (ctDir) params.set('contest', ctDir);
                if (codeShare) {
                    params.set('dir', codeShare.dir);
                    params.set('problem', codeShare.problem);
                }
                const q = params.toString();
                try {
                    history.replaceState(null, '', q ? location.pathname + '?' + q : location.pathname);
                } catch {}
            }
            let codeCopyText = '';
            let codeInlined = [];

            function ensureCopyBtn() {
                if (!copyBtn) {
                    copyBtn = document.getElementById('modalCopy');
                    copyBtn.addEventListener('click', async () => {
                        if (!codeCopyText) return;
                        let ok = false;
                        try {
                            await navigator.clipboard.writeText(codeCopyText);
                            ok = true;
                        } catch (e) {
                            // 非 HTTPS 环境兜底：隐藏 textarea + execCommand
                            try {
                                const ta = document.createElement('textarea');
                                ta.value = codeCopyText;
                                ta.style.position = 'fixed';
                                ta.style.opacity = '0';
                                document.body.appendChild(ta);
                                ta.select();
                                ok = document.execCommand('copy');
                                ta.remove();
                            } catch (e2) {}
                        }
                        copyBtn.textContent = ok
                            ? (codeInlined.length ? '已复制 ✓（内联 ' + codeInlined.join('、') + '）' : '已复制 ✓')
                            : '复制失败';
                        setTimeout(() => { copyBtn.textContent = '复制'; }, 1500);
                    });
                }
                return copyBtn;
            }

            // 行号 / 换行开关（代码模态框）
            let wrapBtn = null;
            let lineBtn = null;
            function ensureModalBtns() {
                if (!wrapBtn) {
                    wrapBtn = document.getElementById('modalWrap');
                    wrapBtn.addEventListener('click', () => {
                        if (editorOpen && cm) {
                            // 编辑态：切换 CodeMirror 的换行
                            const on = !cm.getOption('lineWrapping');
                            cm.setOption('lineWrapping', on);
                            wrapBtn.classList.toggle('on', on);
                        } else {
                            // 查看态：切换查看渲染（pre-wrap）
                            const on = document.getElementById('modalBody').classList.toggle('wrap');
                            wrapBtn.classList.toggle('on', on);
                        }
                    });
                }
                if (!lineBtn) {
                    lineBtn = document.getElementById('modalLine');
                    lineBtn.addEventListener('click', () => {
                        if (editorOpen && cm) {
                            // 编辑态：切换 CodeMirror 的行号
                            const show = !cm.getOption('lineNumbers');
                            cm.setOption('lineNumbers', show);
                            lineBtn.classList.toggle('on', show);
                        } else {
                            // 查看态：切换行号列显隐
                            const off = document.getElementById('modalBody').classList.toggle('no-line');
                            lineBtn.classList.toggle('on', !off);
                        }
                    });
                }
            }

            async function showCode(dir, problem, problemUrl) {
                // 把当前题目（连同已打开的比赛小窗）写进 URL，方便直接分享
                codeShare = { dir, problem };
                writeShareUrl();
                const modal = document.getElementById('codeModal');
                const body = document.getElementById('modalBody');
                const view = document.getElementById('modalView');
                const fn = document.getElementById('modalFilename');
                const link = document.getElementById('modalProblemLink');
                const dl = document.getElementById('modalDl');
                const editBtn = document.getElementById('modalEdit');
                fn.textContent = problem + '.cpp';
                if (problemUrl) {
                    link.href = problemUrl;
                    link.style.display = 'inline';
                } else {
                    link.style.display = 'none';
                }
                ensureCopyBtn();
                ensureModalBtns();
                lineBtn.classList.add('on');
                wrapBtn.classList.remove('on');
                lineBtn.style.display = 'none';
                wrapBtn.style.display = 'none';
                dl.style.display = 'none';
                copyBtn.style.display = 'none';
                editBtn.style.display = 'none';
                showStatus(null);
                if (editorOpen) exitEditor(true);
                body.className = 'modal-body';
                view.innerHTML = '<div class="modal-loading">加载中…</div>';
                modal.classList.add('open');

                try {
                    const res = await fetch(`/api/code?dir=${encodeURIComponent(dir)}&problem=${encodeURIComponent(problem)}`);
                    if (!res.ok) throw new Error('HTTP ' + res.status);
                    const data = await res.json();
                    fn.textContent = data.file;
                    const isPy = data.language === 'python';
                    ctx = {
                        path: dir + '/' + data.file,
                        kind: 'code',
                        lang: isPy ? 'python' : 'text/x-c++src',
                        viewLang: isPy ? 'python' : 'cpp',
                        mtime: data.mtime,
                        label: data.file,
                        editAllowed: !!(data.editable),
                    };
                    codeCopyText = data.full || data.content;
                    codeInlined = data.inlined || [];
                    copyBtn.title = codeInlined.length
                        ? '复制（将内联模板: ' + codeInlined.join('、') + '）'
                        : '复制源代码';
                    copyBtn.style.display = 'inline-block';
                    lineBtn.style.display = 'inline-block';
                    wrapBtn.style.display = 'inline-block';
                    if (EDITABLE && ctx.editAllowed) editBtn.style.display = 'inline-block';
                    // 行号列 + 代码主体；hljs 缺失（CDN 不可用）时退化为纯文本
                    const lines = data.content.split('\n');
                    if (lines.length > 1 && lines[lines.length - 1] === '') lines.pop();
                    view.innerHTML =
                        '<div class="code-shell">'
                        + '<div class="code-gutter" aria-hidden="true">' + lines.map((_, i) => i + 1).join('\n') + '</div>'
                        + '<pre><code class="language-' + data.language + '">' + escapeHtml(data.content) + '</code></pre>'
                        + '</div>';
                    if (typeof hljs !== 'undefined') {
                        hljs.highlightElement(view.querySelector('code'));
                    }
                } catch (err) {
                    view.innerHTML = '<div class="modal-error">加载失败: ' + err.message + '</div>';
                }
            }

            // ── Template 文档查看（markdown 渲染）──
            function addCodeCopyButtons(container) {
                container.querySelectorAll('pre').forEach((pre) => {
                    if (pre.closest('.md-code')) return;
                    const wrap = document.createElement('div');
                    wrap.className = 'md-code';
                    pre.replaceWith(wrap);
                    wrap.appendChild(pre);
                    const btn = document.createElement('button');
                    btn.type = 'button';
                    btn.className = 'copy-btn';
                    btn.textContent = '复制';
                    btn.addEventListener('click', async () => {
                        const code = pre.querySelector('code') || pre;
                        let ok = false;
                        try {
                            await navigator.clipboard.writeText(code.innerText);
                            ok = true;
                        } catch (e) {
                            try {
                                const range = document.createRange();
                                range.selectNodeContents(code);
                                const sel = window.getSelection();
                                sel.removeAllRanges();
                                sel.addRange(range);
                                ok = document.execCommand('copy');
                                sel.removeAllRanges();
                            } catch (e2) {}
                        }
                        btn.textContent = ok ? '已复制' : '复制失败';
                        btn.classList.add(ok ? 'copied' : 'failed');
                        setTimeout(() => {
                            btn.textContent = '复制';
                            btn.classList.remove('copied', 'failed');
                        }, 1500);
                    });
                    wrap.appendChild(btn);
                });
            }

            async function showMarkdown(file) {
                const modal = document.getElementById('codeModal');
                const body = document.getElementById('modalBody');
                const view = document.getElementById('modalView');
                const fn = document.getElementById('modalFilename');
                const link = document.getElementById('modalProblemLink');
                const dl = document.getElementById('modalDl');
                const editBtn = document.getElementById('modalEdit');
                fn.textContent = file;
                link.style.display = 'none';
                dl.href = '/Template/' + encodeURIComponent(file);
                dl.setAttribute('download', file);
                dl.style.display = 'inline-block';
                ensureCopyBtn();
                ensureModalBtns();
                lineBtn.style.display = 'none';
                wrapBtn.style.display = 'none';
                copyBtn.style.display = 'none';
                editBtn.style.display = 'none';
                showStatus(null);
                if (editorOpen) exitEditor(true);
                body.className = 'modal-body markdown';
                view.innerHTML = '<div class="modal-loading">加载中…</div>';
                modal.classList.add('open');

                try {
                    const path = 'Template/' + file;
                    const res = await fetch('/api/file?path=' + encodeURIComponent(path));
                    if (!res.ok) throw new Error('HTTP ' + res.status);
                    const data = await res.json();
                    ctx = {
                        path: path,
                        kind: 'markdown',
                        lang: 'markdown',
                        mtime: data.mtime,
                        viewLang: null,
                        label: file,
                        editAllowed: !!(data.writable),
                    };
                    if (EDITABLE && ctx.editAllowed) editBtn.style.display = 'inline-block';
                    renderMarkdownInto(view, data.content);
                } catch (err) {
                    view.innerHTML = '<div class="modal-error">加载失败: ' + err.message + '</div>';
                }
            }

            // 把 markdown 文本渲染进容器（含 hljs 高亮与代码块复制按钮）
            function renderMarkdownInto(container, text) {
                if (typeof marked !== 'undefined') {
                    container.innerHTML = marked.parse(text);
                    if (typeof hljs !== 'undefined') {
                        container.querySelectorAll('pre code').forEach((el) => hljs.highlightElement(el));
                    }
                } else {
                    // CDN 不可用时退化为纯文本
                    container.innerHTML = '<pre style="padding:1rem;white-space:pre-wrap;font-size:0.82rem">'
                        + escapeHtml(text)
                        + '</pre>';
                }
                addCodeCopyButtons(container);
            }

            // ── Template 文档列表 ──
            function renderTemplate(items) {
                const list = document.getElementById('template-list');
                if (!list) return;
                list.innerHTML = '';
                (items || []).forEach((t) => {
                    const card = document.createElement('div');
                    card.className = 'template-item';
                    card.title = '查看文档';

                    const head = document.createElement('div');
                    head.className = 'doc-head';

                    const icon = document.createElement('span');
                    icon.className = 'doc-icon';
                    icon.textContent = 'MD';

                    const name = document.createElement('span');
                    name.className = 'doc-name';
                    name.textContent = t.name;

                    head.appendChild(icon);
                    head.appendChild(name);

                    const foot = document.createElement('div');
                    foot.className = 'doc-foot';

                    const hint = document.createElement('span');
                    hint.className = 'doc-hint';
                    hint.textContent = 'Markdown';

                    const dl = document.createElement('a');
                    dl.className = 'dl-btn';
                    dl.textContent = '下载';
                    dl.href = '/Template/' + encodeURIComponent(t.file);
                    dl.setAttribute('download', t.file);
                    dl.addEventListener('click', (e) => e.stopPropagation());

                    foot.appendChild(hint);
                    foot.appendChild(dl);

                    card.appendChild(head);
                    card.appendChild(foot);
                    card.addEventListener('click', () => showMarkdown(t.file));
                    list.appendChild(card);
                });
            }

            // ── Downloads 文件列表（每个文件一个下载按钮）──
            function formatBytes(n) {
                if (n == null || !Number.isFinite(n)) return '';
                const units = ['B', 'KB', 'MB', 'GB', 'TB'];
                let i = 0;
                let v = n;
                while (v >= 1024 && i < units.length - 1) {
                    v /= 1024;
                    i++;
                }
                return (i === 0 ? String(n) : v.toFixed(1)) + ' ' + units[i];
            }

            function fileExtLabel(name) {
                const m = /\.([A-Za-z0-9]{1,5})$/.exec(name || '');
                return m ? m[1].toUpperCase() : 'FILE';
            }

            function renderDownloads(items) {
                const list = document.getElementById('downloads-list');
                if (!list) return;
                list.innerHTML = '';
                (items || []).forEach((f) => {
                    const card = document.createElement('a');
                    card.className = 'template-item download-item';
                    card.href = '/Downloads/' + encodeURIComponent(f.file);
                    card.setAttribute('download', f.file);
                    card.title = '下载 ' + f.file;

                    const head = document.createElement('div');
                    head.className = 'doc-head';
                    const icon = document.createElement('span');
                    icon.className = 'doc-icon';
                    icon.textContent = fileExtLabel(f.file);
                    const name = document.createElement('span');
                    name.className = 'doc-name';
                    name.textContent = f.file;
                    head.appendChild(icon);
                    head.appendChild(name);

                    const foot = document.createElement('div');
                    foot.className = 'doc-foot';
                    const hint = document.createElement('span');
                    hint.className = 'doc-hint';
                    hint.textContent = formatBytes(f.size);
                    const dl = document.createElement('span');
                    dl.className = 'dl-btn';
                    dl.textContent = '下载';
                    foot.appendChild(hint);
                    foot.appendChild(dl);

                    card.appendChild(head);
                    card.appendChild(foot);
                    list.appendChild(card);
                });
            }

            // ── 资源区（模板文档 + 文件下载，合并为一个板块）──
            function renderResources(data) {
                renderTemplate(data.template);
                renderDownloads(data.downloads);
                const tCount = (data.template || []).length;
                const dCount = (data.downloads || []).length;
                const tBadge = document.getElementById('rescount-template');
                const dBadge = document.getElementById('rescount-downloads');
                if (tBadge) tBadge.textContent = tCount ? tCount + ' 份' : '';
                if (dBadge) dBadge.textContent = dCount ? dCount + ' 个' : '';
                const section = document.getElementById('section-resources');
                if (section) section.style.display = tCount + dCount > 0 ? 'block' : 'none';
            }

            // ── 导航溢出提示：放不下时右端渐隐，暗示可以横向滑动 ──
            function updateNavOverflow() {
                const links = document.querySelector('.nav-links');
                if (!links) return;
                links.classList.toggle('is-overflowing', links.scrollWidth > links.clientWidth + 1);
            }
            let navResizeTimer = null;
            window.addEventListener('resize', () => {
                clearTimeout(navResizeTimer);
                navResizeTimer = setTimeout(updateNavOverflow, 120);
            });

            function closeCodeView(e) {
                if (e && e.target !== document.getElementById('codeModal')) return;
                closeModal();
            }

            function closeModal() {
                const doClose = () => {
                    if (editorOpen) exitEditor(true);
                    document.getElementById('codeModal').classList.remove('open');
                    // 关闭代码窗：比赛小窗还开着就回落为 ?contest=…，否则清空分享参数
                    codeShare = null;
                    writeShareUrl();
                };
                if (editorOpen && editorDirty) {
                    uiConfirm({
                        title: '未保存的更改',
                        message: '当前文件还有未保存的修改，关闭将丢失这些修改。',
                        okText: '仍要关闭',
                        cancelText: '继续编辑',
                        danger: true,
                    }).then((ok) => { if (ok) doClose(); });
                    return;
                }
                doClose();
            }

            // ── 比赛信息小窗（点击比赛卡片打开）──
            // 卡片上题目 pill 的行为不变；整卡点击改为开这里，原比赛链接收进小窗当按钮
            let ctDir = null;          // 小窗当前展示的比赛目录（数据刷新后据此重绘）

            function findContestByDir(dir) {
                if (!lastData || !dir) return null;
                for (const key of ['atcoder', 'codeforces', 'nowcoder', 'hdu', 'xcpc', 'course']) {
                    for (const c of lastData[key] || []) {
                        if (c.dir === dir) return c;
                    }
                }
                return null;
            }

            function renderContestView(c) {
                const done = !!c.finished;
                document.getElementById('ctName').textContent = c.name;
                const tag = document.getElementById('ctTag');
                tag.className = 'ct-tag ' + (done ? 'complete' : 'incomplete');
                tag.textContent = done ? '✓ 已补完' : '待补题';

                // 进度：total 未知时只报已做题数，不编造百分比
                const countEl = document.getElementById('ctCount');
                countEl.textContent = c.total != null ? c.solvedCount + '/' + c.total : c.solvedCount + ' 题';
                countEl.classList.toggle('done', done);

                const bar = document.getElementById('ctBar');
                const barWrap = bar.parentElement;
                const pctEl = document.getElementById('ctPct');
                const known = c.total != null && c.total > 0;
                barWrap.classList.toggle('done', done);
                barWrap.style.visibility = known ? '' : 'hidden';
                pctEl.style.display = known ? '' : 'none';
                if (known) {
                    const pct = Math.min(100, Math.round((c.solvedCount / c.total) * 100));
                    bar.style.width = pct + '%';
                    pctEl.textContent = pct + '%';
                }

                // 题目网格：已做 → 代码小窗；未做 → 原题页面；都没有则禁用
                const grid = document.getElementById('ctGrid');
                grid.innerHTML = '';
                const problems = c.allProblems || (c.solved || []).map((id) => ({ id, solved: true, url: null }));
                problems.forEach((p) => {
                    const btn = document.createElement('button');
                    btn.type = 'button';
                    btn.className = 'prob ' + (p.solved ? 'solved' : 'unsolved');
                    btn.textContent = p.id;
                    if (p.solved && c.dir) {
                        btn.title = '查看代码';
                        btn.addEventListener('click', () => showCode(c.dir, p.id, p.url));
                    } else if (p.url) {
                        btn.title = '待补题 — 打开题目页面';
                        btn.addEventListener('click', () => window.open(p.url, '_blank', 'noopener'));
                    } else {
                        btn.title = '待补题';
                        btn.disabled = true;
                    }
                    grid.appendChild(btn);
                });

                // 底栏：目录路径 + 原比赛链接（有才显示）+ 比赛设置（仅 --edit）
                document.getElementById('ctPath').textContent = c.dir || '';
                const link = document.getElementById('ctLink');
                if (c.url) {
                    link.href = c.url;
                    link.style.display = '';
                } else {
                    link.style.display = 'none';
                }
                document.getElementById('ctCfg').style.display = EDITABLE && c.dir ? '' : 'none';

                // 缺什么就明说，省得疑惑「按钮去哪了」（缺 config 时 total 可能来自平台默认值，故分开表述）
                const notes = [];
                if (!c.hasConfig) notes.push('未配置 .config.json');
                if (!c.url) notes.push('没有比赛链接');
                if (c.total == null) notes.push('总题数未知，进度按已做题数显示');
                const note = document.getElementById('ctNote');
                note.textContent = notes.join(' · ');
                note.style.display = notes.length ? '' : 'none';
            }

            function showContest(c) {
                if (!c || !c.dir) return;
                ctDir = c.dir;
                renderContestView(c);
                ensureEditBtns();
                // 覆盖式绑定：每次打开都指向当前这场比赛
                document.getElementById('ctCfg').onclick = () => {
                    const cur = findContestByDir(ctDir);
                    if (cur) openCfg(cur);
                };
                document.getElementById('contestModal').classList.add('open');
                writeShareUrl();
            }

            function closeContestView(e) {
                if (e && e.target !== document.getElementById('contestModal')) return;
                const wasOpen = document.getElementById('contestModal').classList.contains('open');
                document.getElementById('contestModal').classList.remove('open');
                ctDir = null;
                // 仅实际关闭过才改写 URL，避免 ESC 兜底调用时误清分享参数
                if (wasOpen) writeShareUrl();
            }

            // 数据刷新（SSE / 保存设置后）时同步已打开的小窗，避免显示过期状态
            function syncContestView() {
                if (!ctDir) return;
                const cur = findContestByDir(ctDir);
                if (cur) renderContestView(cur);
                else closeContestView();
            }

            // ═══ 网页编辑（--edit）：查看/编辑双态 + 保存 ═══
            let EDITABLE = false;          // GET /api/capabilities 结果
            let cm = null;                 // CodeMirror 实例
            let cmLibLoaded = null;        // CM 懒加载 promise
            let editorOpen = false;        // 当前是否处于编辑态
            let editorDirty = false;
            let editorViewClass = 'modal-body';   // 退出编辑时恢复的 body class
            let ctx = null;                // 当前查看/编辑目标
            let cfgPath = null;            // config 表单当前文件
            let cfgMtime = null;
            let toastTimer = null;

            const CM_CSS = '/vendor/codemirror/codemirror.min.css';
            const CM_SCRIPTS = [
                '/vendor/codemirror/codemirror.min.js',
                '/vendor/codemirror/mode/clike/clike.min.js',
                '/vendor/codemirror/mode/python/python.min.js',
                '/vendor/codemirror/mode/xml/xml.min.js',
                '/vendor/codemirror/mode/css/css.min.js',
                '/vendor/codemirror/mode/javascript/javascript.min.js',
                '/vendor/codemirror/mode/markdown/markdown.min.js',
                '/vendor/codemirror/addon/edit/closebrackets.min.js',
                '/vendor/codemirror/addon/edit/matchbrackets.min.js',
                '/vendor/codemirror/addon/selection/active-line.min.js',
            ];

            const LANG_LABEL = {
                'text/x-c++src': 'C++17',
                python: 'Python',
                markdown: 'Markdown',
            };

            function showToast(msg, isErr) {
                const t = document.getElementById('toast');
                t.textContent = msg;
                t.className = 'toast show' + (isErr ? ' err' : '');
                clearTimeout(toastTimer);
                toastTimer = setTimeout(() => { t.className = 'toast'; }, 2400);
            }

            // ── 自绘确认对话框（替代浏览器原生 confirm）──
            let uiConfirmResolve = null;
            function uiConfirm(opts) {
                const { title = '确认', message, okText = '确定', cancelText = '取消', danger = false, okTitle = '' } = opts || {};
                if (uiConfirmResolve) uiSettle(false);   // 已有未决对话框则先取消
                const modal = document.getElementById('confirmModal');
                document.getElementById('confirmTitle').textContent = title;
                document.getElementById('confirmMsg').textContent = message || '';
                const ok = document.getElementById('confirmOk');
                const cancel = document.getElementById('confirmCancel');
                ok.textContent = okText;
                ok.title = okTitle;
                ok.classList.toggle('danger', !!danger);
                cancel.textContent = cancelText;
                modal.classList.add('open');
                ok.focus();
                return new Promise((resolve) => {
                    uiConfirmResolve = (val) => {
                        uiConfirmResolve = null;
                        modal.classList.remove('open');
                        resolve(val);
                    };
                });
            }
            function uiSettle(val) {
                if (uiConfirmResolve) uiConfirmResolve(val);
                else document.getElementById('confirmModal').classList.remove('open');
            }

            function loadEditorLibs() {
                if (cmLibLoaded) return cmLibLoaded;
                cmLibLoaded = new Promise((resolve, reject) => {
                    const link = document.createElement('link');
                    link.rel = 'stylesheet';
                    link.href = CM_CSS;
                    document.head.appendChild(link);
                    let rest = CM_SCRIPTS.length;
                    let failed = false;
                    // 任一脚本失败立即 reject（不能等全部完成——否则失败的 mode 会被吞掉，
                    // 编辑器能打开但对应语言没有语法高亮）
                    const done = (ok, src) => {
                        if (failed) return;
                        if (!ok) {
                            failed = true;
                            reject(new Error('CodeMirror 资源加载失败: ' + src.split('/').pop()));
                            return;
                        }
                        if (--rest === 0) resolve();
                    };
                    CM_SCRIPTS.forEach((src) => {
                        const s = document.createElement('script');
                        // 关键：动态插入的 script 默认按 async 并行执行、顺序无保证，
                        // 会导致 mode/addon 先于 codemirror.min.js 执行而报
                        // 「CodeMirror is not defined」→ mode 注册失败 → 无语法高亮。
                        // async=false 强制按插入顺序串行执行（核心 → mode → addon）。
                        s.async = false;
                        s.src = src;
                        s.onload = () => done(true);
                        s.onerror = () => done(false, src);
                        document.head.appendChild(s);
                    });
                });
                return cmLibLoaded;
            }

            // 编辑状态栏（保存按钮旁的提示文本）
            function showStatus(text, dirty) {
                const st = document.getElementById('editStatus');
                if (!text) { st.style.display = 'none'; st.textContent = ''; return; }
                st.style.display = 'inline';
                st.textContent = text;
                st.classList.toggle('dirty', !!dirty);
            }

            function setDirty(d) {
                editorDirty = d;
                const sb = document.getElementById('modalSave');
                if (!sb) return;
                if (d) {
                    sb.textContent = '● 保存';
                    sb.classList.add('on');
                    showStatus('● 未保存', true);
                } else {
                    sb.textContent = '保存';
                    sb.classList.remove('on');
                }
            }

            // 保存成功：状态栏时间 + 按钮短暂打勾
            let saveFlashTimer = null;
            function markSaved() {
                const sb = document.getElementById('modalSave');
                if (sb) {
                    sb.textContent = '✓ 已保存';
                    clearTimeout(saveFlashTimer);
                    saveFlashTimer = setTimeout(() => {
                        if (!editorDirty) sb.textContent = '保存';
                    }, 1400);
                }
                showStatus('已保存 ' + new Date().toLocaleTimeString('zh-CN', { hour12: false }), false);
            }

            // 底部状态栏：光标行列
            function updateEbPos() {
                if (!cm) return;
                const c = cm.getCursor();
                const el = document.getElementById('ebPos');
                if (el) el.textContent = '行 ' + (c.line + 1) + ', 列 ' + (c.ch + 1);
            }

            function showEditBtnIfNeeded() {
                const editBtn = document.getElementById('modalEdit');
                if (EDITABLE && ctx && ctx.editAllowed && !editorOpen && editBtn) {
                    editBtn.style.display = 'inline-block';
                }
            }

            function ensureEditBtns() {
                const bind = (id, fn) => {
                    const el = document.getElementById(id);
                    if (el && !el.dataset.bound) { el.dataset.bound = '1'; el.addEventListener('click', fn); }
                };
                bind('modalEdit', () => enterEdit());
                bind('modalSave', () => saveFile(false));
                bind('modalCancel', () => exitEditor(false));
                bind('cfgSave', () => saveCfg());
                bind('cfgCancel', () => closeCfgView());
                bind('mkSave', () => mkCreate());
                bind('mkCancel', () => closeMkView());
                bind('confirmOk', () => uiSettle(true));
                bind('confirmCancel', () => uiSettle(false));
                const mkId = document.getElementById('mkId');
                if (mkId && !mkId.dataset.pv) {
                    mkId.dataset.pv = '1';
                    mkId.addEventListener('input', updateMkPreview);
                }
                document.querySelectorAll('input[name="mkLang"]').forEach((r) => {
                    if (!r.dataset.pv) { r.dataset.pv = '1'; r.addEventListener('change', updateMkPreview); }
                });
            }

            async function enterEdit() {
                if (editorOpen || !ctx || !ctx.editAllowed) return;
                ensureEditBtns();
                const body = document.getElementById('modalBody');
                const view = document.getElementById('modalView');
                const host = document.getElementById('modalEditHost');
                const editBtn = document.getElementById('modalEdit');
                const saveBtn = document.getElementById('modalSave');
                const cancelBtn = document.getElementById('modalCancel');
                editBtn.disabled = true;
                saveBtn.disabled = true;
                cancelBtn.disabled = true;
                try {
                    // 编辑基线 = 磁盘最新内容（同时拿 mtime 做乐观锁）
                    const res = await fetch('/api/file?path=' + encodeURIComponent(ctx.path));
                    if (!res.ok) throw new Error('HTTP ' + res.status);
                    const data = await res.json();
                    if (!EDITABLE || !data.writable) {
                        showToast('该实例未开启编辑（需 node server.js --edit 启动）', true);
                        return;
                    }
                    ctx.mtime = data.mtime;
                    await loadEditorLibs();
                    if (typeof CodeMirror === 'undefined') throw new Error('CodeMirror 未加载');
                    editorViewClass = body.className;
                    body.className = 'modal-body editing';
                    view.style.display = 'none';
                    host.style.display = 'flex';
                    host.innerHTML = '';
                    const ta = document.createElement('textarea');
                    host.appendChild(ta);
                    cm = CodeMirror.fromTextArea(ta, {
                        mode: ctx.lang,
                        lineNumbers: lineBtn ? lineBtn.classList.contains('on') : true,
                        lineWrapping: wrapBtn ? wrapBtn.classList.contains('on') : false,
                        indentUnit: 4,
                        tabSize: 4,
                        autoCloseBrackets: true,
                        matchBrackets: true,
                        styleActiveLine: true,
                        extraKeys: { 'Shift-Tab': 'indentLess' },
                    });
                    cm.setValue(data.content);
                    cm.clearHistory();
                    cm.on('change', () => setDirty(true));
                    cm.on('cursorActivity', updateEbPos);
                    updateEbPos();
                    // 高亮自检：把实际生效的 mode 名显示在状态栏（如「C++17 · clike」）；
                    // 若 mode 未注册（null）则重设一次并提示，便于定位无高亮问题
                    setTimeout(() => {
                        if (!cm) return;
                        try {
                            const mn = cm.getMode().name;
                            const langEl = document.getElementById('ebLang');
                            if (mn && mn !== 'null') {
                                if (langEl) langEl.textContent = (LANG_LABEL[ctx.lang] || ctx.lang) + ' · ' + mn;
                            } else {
                                cm.setOption('mode', ctx.lang);
                                cm.refresh();
                                showToast('语法模式未生效，已尝试重新加载', true);
                            }
                        } catch {}
                    }, 300);
                    editBtn.style.display = 'none';
                    saveBtn.style.display = 'inline-block';
                    cancelBtn.style.display = 'inline-block';
                    // 编辑态视觉：header 徽标 + 指示条 + 底部状态栏
                    document.getElementById('codeModalHeader').classList.add('editing');
                    document.getElementById('editBadge').style.display = 'inline-block';
                    document.getElementById('editorBar').style.display = 'flex';
                    document.getElementById('ebLang').textContent = LANG_LABEL[ctx.lang] || ctx.lang;
                    editorOpen = true;
                    showStatus('可编辑 · 点「保存」写入', false);
                    cm.focus();
                } catch (err) {
                    showToast(err.message, true);
                    body.className = editorViewClass;
                    view.style.display = '';
                    host.style.display = 'none';
                } finally {
                    editBtn.disabled = false;
                    saveBtn.disabled = false;
                    cancelBtn.disabled = false;
                }
            }

            // 退出编辑态回查看。force=true 时丢弃未保存改动（切换文件/关闭用）
            async function exitEditor(force) {
                if (!editorOpen) return;
                if (editorDirty && !force) {
                    const ok = await uiConfirm({
                        title: '放弃未保存的修改？',
                        message: '当前文件还有未保存的更改，返回查看将丢弃这些修改。',
                        okText: '丢弃修改',
                        cancelText: '继续编辑',
                        danger: true,
                    });
                    if (!ok) return;
                }
                const body = document.getElementById('modalBody');
                const view = document.getElementById('modalView');
                const host = document.getElementById('modalEditHost');
                const editBtn = document.getElementById('modalEdit');
                const saveBtn = document.getElementById('modalSave');
                const cancelBtn = document.getElementById('modalCancel');
                // 先把 CM 的行号/换行选项读出来（toTextArea 后 cm 失效），退出后同步回查看态
                let cmLine = null, cmWrap = null;
                if (cm) {
                    cmLine = cm.getOption('lineNumbers');
                    cmWrap = cm.getOption('lineWrapping');
                    cm.toTextArea();
                    cm = null;
                }
                host.innerHTML = '';
                host.style.display = 'none';
                view.style.display = '';
                body.className = editorViewClass || 'modal-body';
                if (ctx && ctx.kind === 'code') {
                    if (cmLine != null) {
                        body.classList.toggle('no-line', !cmLine);
                        lineBtn.classList.toggle('on', cmLine);
                    }
                    if (cmWrap != null) {
                        body.classList.toggle('wrap', cmWrap);
                        wrapBtn.classList.toggle('on', cmWrap);
                    }
                }
                saveBtn.style.display = 'none';
                cancelBtn.style.display = 'none';
                saveBtn.textContent = '保存';
                saveBtn.classList.remove('on');
                document.getElementById('codeModalHeader').classList.remove('editing');
                document.getElementById('editBadge').style.display = 'none';
                document.getElementById('editorBar').style.display = 'none';
                if (ctx && ctx.editAllowed && EDITABLE) editBtn.style.display = 'inline-block';
                showStatus(null);
                editorOpen = false;
                editorDirty = false;
            }

            async function saveFile(force) {
                if (!editorOpen || !cm || !ctx) return;
                // 保存前提醒（force 用于 409 覆盖，已在弹窗中确认过，不再重复询问）
                if (!force) {
                    const ok = await uiConfirm({
                        title: '保存文件',
                        message: '确定将当前修改写入「' + ctx.label + '」吗？\n保存后内容直接落盘（可在 git 历史中找回旧版本）。',
                        okText: '保存',
                        cancelText: '取消',
                    });
                    if (!ok) return;
                }
                const saveBtn = document.getElementById('modalSave');
                saveBtn.disabled = true;
                try {
                    const res = await fetch('/api/file', {
                        method: 'PUT',
                        headers: { 'Content-Type': 'application/json' },
                        body: JSON.stringify({
                            path: ctx.path,
                            content: cm.getValue(),
                            baseMtime: force ? null : ctx.mtime,
                        }),
                    });
                    if (res.status === 409) {
                        const data = await res.json().catch(() => ({}));
                        const goForce = await uiConfirm({
                            title: '文件已被外部修改',
                            message: '磁盘上的「' + ctx.label + '」在您编辑期间被其它途径更新过。\n选择覆盖将丢弃外部的改动；选择载入会放弃您编辑框中的内容。',
                            okText: '仍然覆盖',
                            cancelText: '载入最新',
                            danger: true,
                        });
                        if (goForce) return saveFile(true);
                        // 载入磁盘最新
                        const r2 = await fetch('/api/file?path=' + encodeURIComponent(ctx.path));
                        if (r2.ok) {
                            const d2 = await r2.json();
                            cm.setValue(d2.content);
                            cm.clearHistory();
                            ctx.mtime = d2.mtime;
                        }
                        setDirty(false);
                        showStatus('已载入磁盘最新内容', false);
                        showToast('已载入磁盘最新内容');
                        return;
                    }
                    if (!res.ok) {
                        const data = await res.json().catch(() => ({}));
                        throw new Error(data.error || ('HTTP ' + res.status));
                    }
                    const data = await res.json();
                    ctx.mtime = data.mtime;
                    markSaved();
                    showToast('已保存 ' + new Date().toLocaleTimeString('zh-CN', { hour12: false }));
                    refreshView();   // 更新查看态快照（含 markdown 重渲染）
                } catch (err) {
                    showToast('保存失败: ' + err.message, true);
                } finally {
                    saveBtn.disabled = false;
                }
            }

            // 用磁盘最新内容刷新查看态快照（保存成功后调用，供退出编辑时展示）
            async function refreshView() {
                if (!ctx) return;
                try {
                    const res = await fetch('/api/file?path=' + encodeURIComponent(ctx.path));
                    if (!res.ok) return;
                    const data = await res.json();
                    const view = document.getElementById('modalView');
                    if (ctx.kind === 'markdown') {
                        renderMarkdownInto(view, data.content);
                    } else {
                        const lines = data.content.split('\n');
                        if (lines.length > 1 && lines[lines.length - 1] === '') lines.pop();
                        const lang = ctx.viewLang || 'cpp';
                        view.innerHTML =
                            '<div class="code-shell">'
                            + '<div class="code-gutter" aria-hidden="true">' + lines.map((_, i) => i + 1).join('\n') + '</div>'
                            + '<pre><code class="language-' + lang + '">' + escapeHtml(data.content) + '</code></pre>'
                            + '</div>';
                        if (typeof hljs !== 'undefined') hljs.highlightElement(view.querySelector('code'));
                    }
                } catch {}
            }

            // ── .config.json 比赛设置表单（无 config 时进入「新建」模式）──
            async function openCfg(c) {
                ensureEditBtns();
                cfgPath = c.dir + '/.config.json';
                cfgMtime = null;
                isNewCfg = true;
                document.getElementById('cfgTitle').textContent = c.name;
                document.getElementById('cfgUrl').value = c.url || '';
                document.getElementById('cfgCnt').value = c.total != null ? c.total : '';
                document.getElementById('cfgModal').classList.add('open');
                try {
                    const res = await fetch('/api/file?path=' + encodeURIComponent(cfgPath));
                    if (res.ok) {
                        const d = await res.json();
                        if (d.content) {
                            const j = JSON.parse(d.content);
                            if (j.url != null) document.getElementById('cfgUrl').value = j.url;
                            if (j.cnt != null) document.getElementById('cfgCnt').value = j.cnt;
                            cfgMtime = d.mtime;
                            isNewCfg = false;
                        }
                    }
                } catch {}
            }

            function closeCfgView(e) {
                if (e && e.target !== document.getElementById('cfgModal')) return;
                document.getElementById('cfgModal').classList.remove('open');
            }

            function cfgPayload() {
                const urlIn = document.getElementById('cfgUrl').value.trim();
                const urlEl = document.getElementById('cfgUrl');
                const cntEl = document.getElementById('cfgCnt');
                urlEl.classList.remove('invalid');
                cntEl.classList.remove('invalid');
                let bad = false;
                if (urlIn) {
                    try { new URL(urlIn); } catch { urlEl.classList.add('invalid'); bad = true; }
                }
                const cnt = parseInt(document.getElementById('cfgCnt').value, 10);
                if (!Number.isInteger(cnt) || cnt < 1 || cnt > 40) { cntEl.classList.add('invalid'); bad = true; }
                if (bad) { showToast('请检查输入（链接需合法、题数 1-40）', true); return null; }
                return JSON.stringify({ url: urlIn, cnt }, null, 4) + '\n';
            }

            async function saveCfg() {
                if (!cfgPath) return;
                const content = cfgPayload();
                if (content === null) return;
                ensureEditBtns();
                const saveBtn = document.getElementById('cfgSave');
                saveBtn.disabled = true;
                const send = (method, extra) => fetch('/api/file', {
                    method,
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify(Object.assign({ path: cfgPath, content }, extra)),
                });
                try {
                    let res;
                    if (isNewCfg) {
                        res = await send('POST', {});
                        if (res.status === 409) {
                            // 竞态：已被其它途径创建 → 询问是否转编辑覆盖
                            isNewCfg = false;
                            const ok = await uiConfirm({
                                title: '.config.json 已存在',
                                message: '该 .config.json 刚被其它途径创建（或本就有）。\n要覆盖为当前填写的内容吗？',
                                okText: '覆盖保存',
                                cancelText: '取消',
                                danger: true,
                            });
                            if (!ok) return;
                            res = await send('PUT', { baseMtime: null });
                        }
                    } else {
                        res = await send('PUT', { baseMtime: cfgMtime });
                        if (res.status === 409) {
                            const ok = await uiConfirm({
                                title: '设置已在别处被修改',
                                message: '磁盘上的 .config.json 在您编辑期间被更新过，仍然覆盖吗？',
                                okText: '覆盖保存',
                                cancelText: '取消',
                                danger: true,
                            });
                            if (!ok) return;
                            res = await send('PUT', { baseMtime: null });
                        }
                    }
                    if (!res.ok) {
                        const d = await res.json().catch(() => ({}));
                        throw new Error(d.error || ('HTTP ' + res.status));
                    }
                    const d = await res.json();
                    cfgMtime = d.mtime;
                    showToast(isNewCfg ? '比赛设置已创建' : '比赛设置已保存');
                    closeCfgView();
                    refreshData();   // 立即更新列表（后端已 invalidateCache）
                } catch (err) {
                    showToast('保存失败: ' + err.message, true);
                } finally {
                    saveBtn.disabled = false;
                }
            }

            // ── 新建题解（未解决题 + 角标）──
            let mkCtx = null;      // {dir, url}
            let isNewCfg = true;   // cfg 表单当前是否为「新建」模式

            function openMk(c, p) {
                ensureEditBtns();
                mkCtx = { dir: c.dir, url: p.url || null };
                document.getElementById('mkContestName').textContent = c.name;
                document.getElementById('mkId').value = p.id;
                document.getElementById('mkModal').classList.add('open');
                updateMkPreview();
            }

            function updateMkPreview() {
                const id = document.getElementById('mkId').value.trim();
                const langEl = document.querySelector('input[name="mkLang"]:checked');
                const lang = (langEl && langEl.value) || 'cpp';
                const dirTail = mkCtx && mkCtx.dir ? mkCtx.dir.split('/').pop() + '/' : '';
                document.getElementById('mkPathPreview').textContent = dirTail + (id || '?') + '.' + lang;
            }

            function closeMkView(e) {
                if (e && e.target !== document.getElementById('mkModal')) return;
                document.getElementById('mkModal').classList.remove('open');
            }

            function mkSkeleton(lang) {
                if (lang === 'py') {
                    return 'import sys\n\ninput = sys.stdin.readline\nsys.setrecursionlimit(10 ** 6)\n\n\ndef solve():\n    pass\n\n\nif __name__ == "__main__":\n    solve()\n';
                }
                return '#include <ihxnan>\n\nvoid solve()\n{\n    \n}\n';
            }

            async function mkCreate() {
                if (!mkCtx) return;
                const id = document.getElementById('mkId').value.trim();
                const langEl = document.querySelector('input[name="mkLang"]:checked');
                const lang = (langEl && langEl.value) || 'cpp';
                if (!/^[A-Za-z0-9]+$/.test(id)) {
                    showToast('题号只允许字母和数字（如 A、C1、10、P10446）', true);
                    return;
                }
                const path = mkCtx.dir + '/' + id + '.' + lang;
                ensureEditBtns();
                const saveBtn = document.getElementById('mkSave');
                saveBtn.disabled = true;
                try {
                    const res = await fetch('/api/file', {
                        method: 'POST',
                        headers: { 'Content-Type': 'application/json' },
                        body: JSON.stringify({ path, content: mkSkeleton(lang) }),
                    });
                    if (res.status === 409) {
                        const ok = await uiConfirm({
                            title: '文件已存在',
                            message: id + '.' + lang + ' 已存在。\n要改为直接打开它吗？（不会覆盖原内容）',
                            okText: '打开它',
                            cancelText: '取消',
                        });
                        if (ok) {
                            closeMkView();
                            showCode(mkCtx.dir, id, mkCtx.url);
                        }
                        return;
                    }
                    if (!res.ok) {
                        const d = await res.json().catch(() => ({}));
                        throw new Error(d.error || ('HTTP ' + res.status));
                    }
                    showToast('已创建 ' + id + '.' + lang);
                    closeMkView();
                    showCode(mkCtx.dir, id, mkCtx.url);   // 打开新文件查看，可继续编辑
                    refreshData();                        // 卡片立即转「已解决」
                } catch (err) {
                    showToast('创建失败: ' + err.message, true);
                } finally {
                    saveBtn.disabled = false;
                }
            }

            // ESC 键：依次关闭自绘确认框 / 新建题解 / 设置表单 / 代码模态框 / 比赛小窗（已移除 Ctrl/Cmd+S 快捷键保存）
            document.addEventListener('keydown', (e) => {
                if (e.key === 'Escape') {
                    if (document.getElementById('confirmModal').classList.contains('open')) uiSettle(false);
                    else if (document.getElementById('mkModal').classList.contains('open')) closeMkView();
                    else if (document.getElementById('cfgModal').classList.contains('open')) closeCfgView();
                    else if (document.getElementById('codeModal').classList.contains('open')) closeModal();
                    else closeContestView();
                }
            });

            function escapeHtml(str) {
                return str.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
            }

            // 启动即绑定全部编辑相关按钮（幂等；此前只在 openCfg 等路径触发，
            // 且 script 曾位于 modal 之前导致绑定时机 DOM 未就绪 → 「编辑」首次点击无效）
            function bootEditBindings() {
                if (document.readyState === 'loading') {
                    document.addEventListener('DOMContentLoaded', ensureEditBtns);
                } else {
                    ensureEditBtns();
                }
            }
            bootEditBindings();
            loadData();

            // 清空容器（保留结构，清空子元素）
            function clearGrid(id) {
                const el = document.getElementById(id);
                while (el.firstChild) el.removeChild(el.firstChild);
            }

            // 重新拉取并渲染（不清除 loading 状态，直接替换内容）
            async function refreshData() {
                try {
                    const res = await fetch('/api/data');
                    if (!res.ok) throw new Error('HTTP ' + res.status);
                    const data = await res.json();
                    lastData = data;
                    // 只更新已有板块，不清除 content 容器
                    applyStats(data);
                    renderNav(data);

                    ['atcoder', 'codeforces', 'nowcoder', 'hdu', 'xcpc', 'course'].forEach((key) => {
                        const grid = document.getElementById('grid-' + key);
                        clearGrid('grid-' + key);
                        const list = data[key] || [];
                        renderContestList(grid, list);
                    });

                    renderChapterTree('luogu-content', data.luogu, 'luogu');

                    renderResources(data);
                    applyFilter();
                    syncContestView();
                } catch {}
            }

            // SSE 实时更新
            const badge = document.getElementById('livebadge');
            let evtSource;

            function connectSSE() {
                evtSource = new EventSource('/api/events');

                evtSource.onopen = () => {
                    badge.className = 'live-badge';
                    badge.innerHTML = '<span class="pulse"></span>LIVE';
                };

                evtSource.onmessage = (e) => {
                    try {
                        const msg = JSON.parse(e.data);
                        if (msg.type === 'reload') {
                            refreshData();
                        } else if (msg.type === 'server_restart') {
                            badge.className = 'live-badge reconnecting';
                            badge.innerHTML = '<span class="pulse"></span>重连中…';
                        }
                    } catch {}
                };

                evtSource.onerror = () => {
                    badge.className = 'live-badge reconnecting';
                    badge.innerHTML = '<span class="pulse"></span>重连中…';
                    // EventSource 会自动重连
                };
            }

            // ── 亮/暗色切换（手动偏好覆盖系统偏好）──
            const themeMq = matchMedia('(prefers-color-scheme: dark)');
            const hljsLight = document.getElementById('hljs-light');
            const hljsDark = document.getElementById('hljs-dark');
            function storedTheme() {
                try {
                    const t = localStorage.getItem('ui.theme');
                    return t === 'dark' || t === 'light' ? t : null;
                } catch {
                    return null;
                }
            }
            function currentTheme() {
                return storedTheme() || (themeMq.matches ? 'dark' : 'light');
            }
            function applyTheme(theme) {
                const dark = theme === 'dark';
                document.documentElement.classList.toggle('theme-dark', dark);
                document.documentElement.style.colorScheme = theme;
                hljsLight.disabled = dark;
                hljsDark.disabled = !dark;
            }
            document.getElementById('themeToggle').addEventListener('click', () => {
                const next = currentTheme() === 'dark' ? 'light' : 'dark';
                try {
                    localStorage.setItem('ui.theme', next);
                } catch {}
                applyTheme(next);
            });
            themeMq.addEventListener('change', () => {
                if (!storedTheme()) applyTheme(currentTheme());
            });
            applyTheme(currentTheme());

            connectSSE();
        