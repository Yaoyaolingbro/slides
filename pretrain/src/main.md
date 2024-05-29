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

# 基于蛋白质结构表征的预训练模型

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
## Protein
蛋白质作为生命的基本组成部分，在从酶反应到细胞信号传导的许多生物过程中发挥着关键作用。

蛋白质是由残基组成的大分子，即氨基酸，以链的形式连接在一起。尽管只有20种标准残基类型，但它们的众多组合促成了自然界中发现的蛋白质的巨大多样性。

而对蛋白质的有效理解对于揭示疾病、药物发现和合成生物学的潜在机制至关重要。

> Focus 的重点在于复杂的三维结构和动态行为，这是决定它们的功能多样性的根本

<!--v-->


## 什么是Pretrain Model？

- Pretrain Model是一种在大规模数据上预训练的模型(非常宽泛的定义😂)
- 通过预训练，模型可以学习到数据的分布，提高模型的泛化能力
- Pretrain Model可以用于多种任务，如分类、聚类、生成等

> 所谓的Representation Learning，其实就是AI模型在做的事情

> 而Pretrain Model在大量数据驱动下会在更多的下游任务上表现优异，已经在众多蛋白质下游任务中取得了成功

<!--v-->
## 一点点novel的东西
Yet, the sheer complexity of protein structures and interactions poses challenges. 

> Figure1: Comparisons of PDB (blue)and AlphaFold (red) structures for GB1 (PDB:2GI9) and SARS-Cov-2 RBD bound to human ACE2 (PDB:6M0J, orange & grey).
![20240529163343.png](graph/20240529163343.png)



<!--v-->
## 关于蛋白质结构的BackGround
| 蛋白质基础结构 | SE(3) diffusion model  |
| --- | --- |
|![20240529162959.png](graph/20240529162959.png)| ![20240529165239.png](graph/20240529165239.png) |

<!--v-->
## 蛋白质的重要性和挑战 
- 蛋白质由氨基酸的线性链组成，可折叠成特定的构象，决定了其功能
- 蛋白质结构确定的挑战导致蛋白质结构数据集相对较小
- 最近的工作利用未标记的蛋白质序列数据来学习蛋白质的有效表示
- 基于结构的蛋白质编码器和预训练方法的发展填补了蛋白质功能注释的差距
- 最新的蛋白质结构预测方法使得可以有效地预测大量蛋白质序列的结构
- ......

> SSF(Structure Sequence Function) is all you need!


<!--s-->

<div class="middle center">
<div style="width: 100%">

# Part.2 Related Work & Method

</div>
</div>

<!--v-->
## Protein Encoder
- 全原子级别的蛋白质结构编码器是十分重要的！！！
> 传统的蛋白质结构编码器主要基于图卷积网络(GCN)和自编码器(AE) —— 但是这些方法在处理全原子级别的蛋白质结构时存在一定的局限性（我们真的应当采取这样的方式吗？）

因而我们提出了一种新的蛋白质结构编码器，以适用于attetion-based的框架。

<!--v-->

## Backbone Representation
我们提出的骨干级表示的图示如下：
- ( a )氨基酸i骨架坐标系的构建
- ( b )计算两个氨基酸i和j的骨架坐标系之间的3个欧拉角
- ( c )说明了现有方法和我们提出的方法确定氨基酸i和j之间的相对旋转。紫色虚线表示现有方法如何通过计算沿链的所有主链二面角来确定i和j之间的相对旋转。黄箭头显示了我们的方法如何仅使用三个欧拉角来确定氨基酸i和j之间的相对旋转。

![20240529214502.png](graph/20240529214502.png)

<!--v-->

## Residua Embedding
我们提出的残基嵌入的图示如下：
> 与alphaFold的残基嵌入相比，我们的残基未考虑`180-rotation-symmetric`,但由于原子名称给定，我们无需考虑这个问题。
![20240529214817.png](graph/20240529214817.png)


<!--v-->
## Attention-based Model
关于attention-based model选择，是因为其在处理全原子级别的蛋白质结构时具有更好的性能。
而关于如何将SS（Structure & Sequence information）的选择，我们做了如下的ablation study：
![20240529220515.png](graph/20240529220515.png)

<!--v-->
## Contrastive Learning
- 对比学习是一种无监督学习方法，通过最大化正样本的相似性和负样本的差异性来学习数据的表示

> A blog about Contrastive Learning: [Contrastive Self-Supervised Learning](https://ankeshanand.com/blog/2020/01/26/contrative-self-supervised-learning.html)
> ![20240529213023.png](graph/20240529213023.png)

<!--v-->
## How to Train
结合上述我们所提供的知识，我们的训练模型如下:

![20240529220817.png](graph/20240529220817.png)

> Denoise to be continued......


<!--s-->

<div class="middle center">
<div style="width: 100%">

# Part.3 Experiment & Result

</div>
</div>

<!--s-->

<div class="middle center">
<div style="width: 100%">

# Part.4 Discussion

</div>
</div>

<!--v-->
## 关于一点点RL
我始终认为，目前基于MLP的主流模型思想始终源于一些人类意识的探索思考，而强化学习的潜能始终未被完全挖掘，尤其在for science领域......
![20240529215428.png](graph/20240529215428.png)

<!--v-->
## 图例

![20240529220114.png](graph/20240529220114.png)

<!--s-->

<div class="middle center">
<div style="width: 100%">

# 感谢聆听

> 恳请批评指正！

</div>
</div>

<!--v-->
## 参考文献
[1]	Bin Ma and Richard Johnson. De novo sequencing and homology searching. Molecular & cellular proteomics, 11(2), 2012.

[2]	Bin Ma. Novor: real-time peptide de novo sequencing software. Journal of the American Society for Mass Spectrometry, 26(11):1885–1894, 2015.

[3]	Yue Cao, Payel Das, Vijil Chenthamarakshan, Pin-Yu Chen, Igor Melnyk, and Yang Shen. Fold2seq: A joint sequence(1d)-fold(3d) embedding-based generative model for protein design.

<!--v-->

[4]	Bowen Jing, Stephan Eismann, Pratham N. Soni, and Ron O. Dror. Learning from protein structure with geometric vector perceptrons. In International Conference on Learning Representations, 2021.

[5]	Pedro Hermosilla, Marco Schäfer, Matˇ ej Lang, Gloria Fackelmann, Pere Pau Vázquez, Barbora Kozlíková, Michael Krone, Tobias Ritschel, and Timo Ropinski. Intrinsic-extrinsic convolution and pooling for learning on 3d protein structures.

[6]	Ahmed Elnaggar, Michael Heinzinger, Christian Dallago, Ghalia Rehawi, Wang Yu, Llion Jones, Tom Gibbs, Tamas Feher, Christoph Angerer, Martin Steinegger, Debsindhu Bhowmik, and Burkhard Rost. Prottrans: Towards cracking the language of lifes code through self-supervised deep learning and high performance computing.

<!--v-->

[7]	Pedro Hermosilla and Timo Ropinski. Contrastive representation learning for 3d protein structures. In Submitted to The Tenth International Conference on Learning Representations, 2022.

[8]	Limei Wang, Haoran Liu, Yi Liu, Jerry Kurtin, and Shuiwang Ji. Learning protein representations via complete 3d graph networks. ArXiv, abs/2207.12600, 2022a.

[9]	John Jumper, Richard Evans, Alexander Pritzel, Tim Green, Michael Figurnov, Olaf Ronneberger, Kathryn Tunyasuvunakool, Russ Bates, Augustin Žídek, Anna Potapenko, et al. Highly accurate protein structure prediction with alphafold. Nature, 596(7873):583–589, 2021.
