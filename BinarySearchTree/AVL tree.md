###### tags: `資料結構`
[toc]    

# AVL tree    
Rule: 任何節點的左子樹跟右子樹高度只能差一    
## 證明一顆有n個節點的tree的高度為O(lgn)    



證明:    
假設n(h)為要產生高度為h的AVL tree**所需要的最小節點數**    
因為知道root的左樹跟右樹的關係:只能差一    
又要求**最小節點數**    
所以可以長成下面這樣    
![](https://i.imgur.com/vRINmBW.png)


所以有遞迴關係式    
n(h) = 1 + n(h-1) + n(h-2)    

已知base case : n(1) = 1,n(2) = 2    


生成高度為h的AVL樹所需的最小節點數量為:    
ROOT+高度為h-1的AVL樹所需的最小節點數+高度為h-2的AVL樹所需的最小節點數    

又n(h-1) > n(h-2) + 1    

因此可以將n(h)改寫為    
n(h) > 2*n(h-2)    
(**高度下降二,係數乘2**)

依照此遞迴關係    
n(h-2) > 4*n(h-4)> 8*n(h-6)    

```
n(h) > 2*n(h-2) > 4*n(h-4) > 8*n(h-6) > 2^k * n (h-2k)    
```
```
因此    
n(h) > 2^k * n (h-2k)  
```
已知base case n(1) = 1    

令h-2k = 1 -> 2k = h-1    
k = (h-1)/2    

n(h) > 2^(h-1)/2 * n(2)    

同取lg    
lg(n) > (h-1)/2 + 1    
 
2lgn + 1 > h    

**h<O(lgn)**    



## Blance factor    
平衡因子    
`定義為:左樹高-右樹高`    

左樹高跟右樹高最多只能差1    
**因此當bf = 2 or bf = -2 就代表不平衡**    

**每次插入/刪除,都需要將被改變的路徑上的點重新計算bf,以檢查是否平衡**。    
(**子孫有變動就必須重新計算**)    

插入跟刪除會改變bf!!        
**但並不是整棵樹的每個node都需要重新計算**    
![](https://i.imgur.com/Q7f5n2A.png)
藍色是在紅色路徑上的點,只有這些藍色的點需要重新計算BF    
而綠色的點則不受影響。    

相同的,如果今天將紅色的點從上圖移除,也只有**藍色**的點需要重新計算而已。    

如果重新計算後發現不平衡,**就需要調整樹**。    
![](https://i.imgur.com/3ltYPVm.png)    
插入新節點後    
![](https://i.imgur.com/uSiP4Jt.png)    

發現不平衡出現(bf = -2)    
因此要開始調整樹。    

以下將介紹AVL調整樹的方法:Rotation    

    
## Rotation    
AVL是利用旋轉的方式維持平衡。    
旋轉有四種類型    
1. RR    
2. LL    
3. RL    
4. LR    

要了解旋轉，最簡單的方式就是只看3個node,然後將其調整。    

旋轉的過程很像在拿葡萄,每次將中間的葡萄提起維持平衡。    


### RR    

RR rotation指的是右邊過重,且為RR型。    
<img src=https://i.imgur.com/iYx8X7n.png width="500">

**這時候代表右邊過重,會出現的BF pattern: -2 , -1**    

將中間的node向上提起就能維持平衡了    
![](https://i.imgur.com/RiwLACN.png)



### LL    
LL就是RR的反方向        
LL rotation指的就是左邊過重,且為LL型    
**這時候代表左邊過重,會出現的BF pattern 2,1**      
![](https://i.imgur.com/Qpy1Eui.png)

一樣提起中間的node就行了
![](https://i.imgur.com/aSmFgig.png)



### LR    
顧名思義,整體而言左邊過重,但第二個NODE是右邊過重        
**出現的BF pattern : 2,-1**    
![](https://i.imgur.com/nkq2C68.png)

此時要做的事情:    
先將它變成LL型,再利用LL rotation平衡    

將下面做RR rotation    
![](https://i.imgur.com/fnrMi6Q.png)
![](https://i.imgur.com/dIhSE2F.png)

然後可以再用剛剛的LL rotation搞定    

### RL    


![](https://i.imgur.com/tjXREQV.png)
然後先對中間的點用LL rotation轉成RR,再用RR解掉    

### 總結    

LL : 單純的LL型    
RR : 單純的RR型    
LR : 先做RR再做LL    
RL : 先做LL再做RR    

所以總結:只有兩種操作RR跟LL    
以下將討論general的情況    
並只討論RR跟LL(因為LR,RL就只是兩種的組合)    


## general的情況    
在前面介紹rotation時,都用3個點來簡單觀察    
但實際的case,中間的點可能會有child    
**我們將中間的點往上提的時候,child必須給左邊或右邊**        
https://www.javatpoint.com/rr-rotation-in-avl-tree    
![](https://i.imgur.com/rgQM71h.png)

例如RR rotation,就要將中間的點的left交給A    
```
A->right = B->left    
B->left = A    
```

並且,移動後受影響的點只有:A,B兩點    
**子孫有變動就必須重新計算**        

所一一個RR rotation的操作需要    
```
A->right = B->left    
B->left = A    
重新計算A的bf,height    
重新計算B的bf,height   

計算的順序一定要先A再B    
因為我自己的計算方法為:    
h = max(left_h,right_h)+1    
bf = left_h - right_h    
因此會用到子孫的高度    
現在A是B的子孫,因此A必須先計算完才能給B用    
```


LL rotation    

![](https://i.imgur.com/MOGrVSN.jpg)

```
A->left = B->right    
B->right = A    
重新計算A的bf,height    
重新計算B的bf,height   

計算的順序一定要先A再B      
```

## 何時要重新計算bf,height?    

在最最前面提到過,但因為這很重要所以這邊再次強調    
每次插入/刪除,都需要將被改變的路徑上的點重新計算bf,以檢查是否平衡。
(**子孫有變動就必須重新計算**)    
**而從上面的例子可以發現,進行Rotation後也要重新計算**

**所以每次進行子孫的變動,就要想一下哪些node會受到影響,就必須由低到高重新計算**    
例如RR rotation    
![](https://i.imgur.com/KQ0Gxm8.png)

1. 插入時受到影響的點:   
    T3,A,B     
2. RR rotation時受到影響的點:    
    只有A跟B    


刪除的時候也會有變動    

![](https://i.imgur.com/YYRhlDu.png)

例如刪除12,11的bf與height將受到影響    
![](https://i.imgur.com/5pod3Qt.png)


因此也必須重新計算11的bf跟height,並且檢查是否不平衡    
這個例子11的bf變成2,因此要調整    
使用LL rotation    

調整完受變動的node只有9,11    
而11會在9的下方,因此必須先更新11的bf,height,再更新9的bf跟height    


