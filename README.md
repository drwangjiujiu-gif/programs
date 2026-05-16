# CircuitJS Desktop Portable

这是一个基于 `CircuitJS1` 二次整理的开源仓库，目标是提供：

- 可公开查看的源码
- 可下载的 Windows 离线便携版
- 后续继续开发桌面版时的公开基础

## 说明

- 上游项目：`CircuitJS1`
- 上游仓库：<https://github.com/pfalstad/circuitjs1>
- 当前仓库中的源码目录：`circuitjs-desktop-source/`
- 当前便携版基于 Electron 运行，适合在 Windows 64 位系统离线使用

## 下载方式

- 源码：直接下载本仓库代码
- 便携版：请从 GitHub Releases 页面下载压缩包

说明：

- 不建议把 `electron-v9.3.2-win32-x64` 整个目录直接提交进 GitHub 仓库代码中
- 原因是其中 `electron.exe` 单文件超过 GitHub 普通仓库的 100MB 限制
- 正确做法是：源码进仓库，便携版 zip 作为 Release 附件上传

## 仓库结构

```text
programs/
  circuitjs-desktop-source/
  docs/
  README.md
  LICENSE
  NOTICE.md
```

## 当前修改

在上游基础上，当前已经做了这些整理：

- 修复 Windows 下 `makeSite` 最后一步会卡住的问题
- 调整 Electron 主进程代码，兼容 Electron 9.3.2
- 验证本地网页版本可运行
- 验证 Windows 便携版可运行

## 许可证

- 本仓库当前内容基于 GPL 上游项目衍生整理
- 因此仓库根许可证已切换为 GPL 许可证
- 具体说明见 `NOTICE.md`

## 后续计划

- 整理更正式的软件名称和图标
- 增加发布说明和版本记录
- 对照网页端继续补齐需要保留的体验细节
