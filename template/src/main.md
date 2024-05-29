---
title: 基于蛋白质结构表征的预训练模型
separator: <!--s-->
verticalSeparator: <!--v-->
theme: simple
highlightTheme: github
css: custom.css
revealOptions:
    transition: 'slide'
    transitionSpeed: fast
    center: false
    slideNumber: "c/t"
    width: 1000
---

<div class="middle center">
<div style="width: 100%">
<img src="graph/logo.png" style="margin-bottom: 1em">

# 个人介绍

<hr/>

2024 Spring

By [混合2207 杜宗泽](https://github.com/Yaoyaolingbro)

<div style="text-align: right; margin-top: 1em;">
<p>2024.3.15&emsp;&emsp;&emsp;</p>
</div>


</div>
</div>

<!--s-->

<div class="middle center">
<div style="width: 100%">

# Part.1 Introduction

</div>
</div>

<!--v-->

## 什么是Pretrain Model？

- Pretrain Model是一种在大规模数据上预训练的模型(非常宽泛的定义😂)
- 通过预训练，模型可以学习到数据的分布，提高模型的泛化能力
- Pretrain Model可以用于多种任务，如分类、聚类、生成等

> 所谓的Representation Learning，其实就是AI模型在做的事情
> 而Pretrain Model再大量数据驱动下会在更多的下游任务上表现优异

<!--v-->
## 一点点novel的东西
> Figure1: Comparisons of PDB (blue)and AlphaFold (red) structures for GB1 (PDB:2GI9) and SARS-Cov-2 RBD bound to human ACE2 (PDB:6M0J, orange & grey).
![20240529163343.png](graph/20240529163343.png)


<!--v-->
## 关于蛋白质结构的BackGround
|  |  |
| --- | --- |
|![20240529162959.png](graph/20240529162959.png)|

<!--v-->
## 蛋白质的重要性和挑战
- 蛋白质是细胞的重要组成部分，涉及从药物设计到材料的广泛应用
- 蛋白质由氨基酸的线性链组成，可折叠成特定的构象，决定了其功能
- 蛋白质结构确定的挑战导致蛋白质结构数据集相对较小
- 最近的工作利用未标记的蛋白质序列数据来学习蛋白质的有效表示
- 基于结构的蛋白质编码器和预训练方法的发展填补了蛋白质功能注释的差距
- 基于结构的方法可以更好地学习蛋白质的信息表示
- 最新的蛋白质结构预测方法使得可以有效地预测大量蛋白质序列的结构
- 采用全原子序列+结构等Diffusion模型可以提取蛋白质的表征并应用于药物设计等领域