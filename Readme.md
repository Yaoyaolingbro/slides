# Slides

杜宗泽的 slides 仓库，使用 [reveal-md](https://github.com/webpro/reveal-md) 构建。

**目录页：** https://yaoyaolingbro.github.io/slides/index.html

## 目录

| 标题 | 类别 | 链接 |
|------|------|------|
| 本博贯通经验分享 | 分享交流 | [slides](https://yaoyaolingbro.github.io/slides/sharing/site/index.html) |
| 杜宗泽 个人介绍 | 个人介绍 | [slides](https://yaoyaolingbro.github.io/slides/person/site/index.html) |
| 基于蛋白质结构表征的预训练模型 | 科研报告 | [slides](https://yaoyaolingbro.github.io/slides/pretrain/site/index.html) |
| Mini-Search | 项目 | [slides](https://yaoyaolingbro.github.io/slides/ADS/site/index.html) |
| Crash Course for C | 课程 | [slides](https://yaoyaolingbro.github.io/slides/ICL/slides/index.html) |

## 目录结构

```
slides/
├── index.html          # 公开目录页
├── template/           # 通用模板
├── <topic>/
│   ├── src/            # 源文件（main.md、custom.css、graph/）
│   └── site/           # 构建产物（由 make build 生成）
└── Readme.md
```

## 本地开发

```bash
# 安装依赖
npm install -g reveal-md

# 实时预览
cd <topic>/src
make live

# 构建静态站点
make build

# 构建后 push，GitHub Pages 自动更新
git add . && git commit -m "update slides" && git push
```

## 新增 slides

1. 复制 `template/` 到新目录
2. 编辑 `src/main.md`
3. `make build` 生成 `site/`
4. 在 `index.html` 和本 README 中添加对应条目
5. Push 到 GitHub
