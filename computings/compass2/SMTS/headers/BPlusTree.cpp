#include "BPlusTree.h"

template <class DATA_TYPE>
CNode<DATA_TYPE>::CNode()
{
    this->m_Type = NODE_TYPE_LEAF;
    this->m_Count = 0;
    m_pFather = NULL;
}
template <class DATA_TYPE>
CNode<DATA_TYPE>::~CNode()
{
    DeleteChildren();
}

// 获取一个最近的兄弟结点
template <class DATA_TYPE>
CNode<DATA_TYPE>* CNode<DATA_TYPE>::GetBrother(int& flag)
{
    CNode<DATA_TYPE>* pFather = GetFather();   //获取其父结点指针
    if (NULL == pFather)
    {
        return NULL;
    }

    CNode<DATA_TYPE>* pBrother = NULL;

    for (int i = 1; i <= pFather->GetCount() + 1; i++)   //GetCount()表示获取数据或关键字数，要比指针数小1。
    {
        // 找到本结点的位置
        if (pFather->GetPointer(i) == this)
        {
            if (i == (pFather->GetCount() + 1))   //表示其为父结点的最右边孩子。
            {
                pBrother = pFather->GetPointer(i - 1);    // 本身是最后一个指针，只能找前一个指针
                flag = FLAG_LEFT;
            }
            else
            {
                pBrother = pFather->GetPointer(i + 1);    // 优先找后一个指针
                flag = FLAG_RIGHT;
            }
        }
    }

    return pBrother;
}

// 递归删除子结点
template <class DATA_TYPE>
void CNode<DATA_TYPE>::DeleteChildren()   // 疑问：这里的指针下标是否需要从0开始
{
    for (int i = 1; i <= GetCount(); i++)   //GetCount()为返回结点中关键字即数据的个数
    {
        CNode<DATA_TYPE> * pNode = GetPointer(i);
        if (NULL != pNode)    // 叶子结点没有指针
        {
            pNode->DeleteChildren();
        }

        delete pNode;
    }
}

//将内部节点的关键字和指针分别初始化为0和空
template <class DATA_TYPE>
CInternalNode<DATA_TYPE>::CInternalNode()    
{
    this->m_Type = NODE_TYPE_INTERNAL;

    int i = 0;
    for (i = 0; i < MAXNUM_KEY; i++)
    {
        m_Keys[i] = INVALID;
    }

    for (i = 0; i < MAXNUM_POINTER; i++)
    {
        m_Pointers[i] = NULL;
    }
}
template <class DATA_TYPE>
CInternalNode<DATA_TYPE>::~CInternalNode()
{
    for (int i = 0; i < MAXNUM_POINTER; i++)
    {
        m_Pointers[i] = NULL;
    }
}

// 在中间结点中插入键。
/*疑问：中间结点需要插入值吗？在插入值时，通常都是先找到在叶子结点中的位置，然后再插入。
中间结点通常当叶子结点需要分裂时将分裂后的两个孩子结点插入其中*/
template <class DATA_TYPE>
bool CInternalNode<DATA_TYPE>::Insert(KEY_TYPE value, CNode<DATA_TYPE>* pNode,DATA_TYPE data)
{
    int i;
    // 如果中间结点已满，直接返回失败
    if (GetCount() >= MAXNUM_KEY)
    {
        return false;
    }

    int j = 0;

    // 找到要插入键的位置
    for (i = 0; (value > m_Keys[i]) && ( i < this->m_Count); i++)
    {
    }

    // 当前位置及其后面的键依次后移，空出当前位置
    for (j = this->m_Count; j > i; j--)
    {
        m_Keys[j] = m_Keys[j - 1];
    }

    // 当前位置及其后面的指针依次后移
    for (j = this->m_Count + 1; j > i + 1; j--)
    {
        m_Pointers[j] = m_Pointers[j - 1];
    }
   
    // 把键和指针存入当前位置
    m_Keys[i] = value;
    m_Pointers[i + 1] = pNode;    // 注意是第i+1个指针而不是第i个指针
    pNode->SetFather(this);      // 非常重要  该函数的意思是插入关键字value及其所指向子树

    this->m_Count++;

    // 返回成功
    return true;
}

// 在中间结点中删除键，以及该键后的指针
template <class DATA_TYPE>
bool CInternalNode<DATA_TYPE>::Delete(KEY_TYPE key)
{
    int i,j,k;
    for (i = 0; (key >= m_Keys[i]) && (i < this->m_Count); i++)
    {
    }

    for (j = i - 1; j < this->m_Count - 1; j++)
    {
        m_Keys[j] = m_Keys[j + 1];
    }
    m_Keys[j] = INVALID;

    for (k = i; k < this->m_Count; k++)
    {
        m_Pointers[k] = m_Pointers[k + 1];
    }
    m_Pointers[k] = NULL;

    this->m_Count--;

    return true;
}

/* 分裂中间结点
分裂中间结点和分裂叶子结点完全不同，因为中间结点不仅有2V键，还有2V+1指针，如果单纯地一分为2，指针将无法分 配。
因此根据http://www.seanster.com/BplusTree/BplusTree.html ，分裂中 间结点的算法是：
根据要插入的键key判断：
(1)如果key小于第V个键，则把第V个键提出来,其左右的键分别分到两个结点中
(2) 如果key大于第V+1个键，则把第V+1个键提出来,其左右的键分别分到两个结点中
(3)如果key介于第V和V+1个键之间，则把key作为 要提出的键，原来的键各分一半到两个结点中
提出来的RetKey作用是便于后续插入到祖先结点
*/
template <class DATA_TYPE>
KEY_TYPE CInternalNode<DATA_TYPE>::Split(CInternalNode<DATA_TYPE>* pNode, KEY_TYPE key)  //key是新插入的值，pNode是分裂结点
{
    int i = 0, j = 0;
   
    // 如果要插入的键值在第V和V+1个键值中间，需要翻转一下，因此先处理此情况
    if ((key > this->GetElement(ORDER_V)) && (key < this->GetElement(ORDER_V + 1)))
    {
        // 把第V+1 -- 2V个键移到指定的结点中

        for (i = ORDER_V + 1; i <= MAXNUM_KEY; i++)
        {
            j++;
            pNode->SetElement(j, this->GetElement(i),INVALID);
            this->SetElement(i, INVALID,INVALID);
        }

        // 把第V+2 -- 2V+1个指针移到指定的结点中
        j = 0;
        for (i = ORDER_V + 2; i <= MAXNUM_POINTER; i++)
        {
            j++;
            this->GetPointer(i)->SetFather(pNode);    // 重新设置子结点的父亲
            pNode->SetPointer(j, this->GetPointer(i));
            this->SetPointer(i, INVALID);
        }

        // 设置好Count个数
        this->SetCount(ORDER_V);
        pNode->SetCount(ORDER_V);

        // 把原键值返回
        return key;
    }

    // 以下处理key小于第V个键值或key大于第V+1个键值的情况

    // 判断是提取第V还是V+1个键
    int position = 0;
    if (key < this->GetElement(ORDER_V))
    {
        position = ORDER_V;
    }
    else
    {
        position = ORDER_V + 1;
    }

    // 把第position个键提出来，作为新的键值返回
    KEY_TYPE RetKey = this->GetElement(position);

    // 把第position+1 -- 2V个键移到指定的结点中
    j = 0;
    for (i = position + 1; i <= MAXNUM_KEY; i++)
    {
        j++;
        pNode->SetElement(j, this->GetElement(i),INVALID );
        this->SetElement(i, INVALID,INVALID);
    }

    // 把第position+1 -- 2V+1个指针移到指定的结点中(注意指针比键多一个)
    j = 0;
    for (i = position + 1; i <= MAXNUM_POINTER; i++)
    {
        j++;
        this->GetPointer(i)->SetFather(pNode);    // 重新设置子结点的父亲
        pNode->SetPointer(j, this->GetPointer(i));
        this->SetPointer(i, INVALID);
    }

    // 清除提取出的位置
    this->SetElement(position, INVALID,INVALID);

    // 设置好Count个数
    this->SetCount(position - 1);
    pNode->SetCount(MAXNUM_KEY - position);


    return RetKey;
}

//结合结点，把指定中间结点的数据全部剪切到本中间结点
template <class DATA_TYPE>
bool CInternalNode<DATA_TYPE>::Combine(CNode<DATA_TYPE>* pNode)
{
    // 参数检查
    if (this->GetCount() + pNode->GetCount() + 1> MAXNUM_DATA)    // 预留一个新键的位置
    {
        return false;
    }
   
    // 取待合并结点的第一个孩子的第一个元素作为新键值
    KEY_TYPE NewKey = pNode->GetPointer(1)->GetElement(1);  //疑问：感觉应该改为KEY_TYPE NewKey = pNode->GetElement(1);

    m_Keys[this->m_Count] = NewKey;
    this->m_Count++;
    m_Pointers[this->m_Count] = pNode->GetPointer(1);   //疑问：感觉应该为m_Pointers[this->m_Count+1] = pNode->GetPointer(1);

    for (int i = 1; i <= pNode->GetCount(); i++)
    {
        m_Keys[this->m_Count] = pNode->GetElement(i);
        this->m_Count++;
        m_Pointers[this->m_Count] = pNode->GetPointer(i+1);
    }

    return true;
}

// 从另一结点移一个元素到本结点
template <class DATA_TYPE>
bool CInternalNode<DATA_TYPE>::MoveOneElement(CNode<DATA_TYPE>* pNode)
{
    // 参数检查
    if (this->GetCount() >= MAXNUM_DATA)
    {
        return false;
    }

    int i,j;


    // 兄弟结点在本结点左边
    if (pNode->GetElement(1) < this->GetElement(1))
    {
        // 先腾出位置
        for (i = this->m_Count; i > 0; i--)
        {
            m_Keys[i] = m_Keys[i -1];
        }
        for (j = this->m_Count + 1; j > 0; j--)
        {
            m_Pointers[j] = m_Pointers[j -1];
        }

        // 赋值
        // 第一个键值不是兄弟结点的最后一个键值，而是本结点第一个子结点的第一个元素的值
        m_Keys[0] = GetPointer(1)->GetElement(1);
        // 第一个子结点为兄弟结点的最后一个子结点
        m_Pointers[0] = pNode->GetPointer(pNode->GetCount() + 1);
       
        // 修改兄弟结点
        pNode->SetElement(pNode->GetCount(), INVALID,INVALID);
        pNode->SetPointer(pNode->GetCount() + 1, INVALID);
    }
    else    // 兄弟结点在本结点右边
    {
        // 赋值
        // 最后一个键值不是兄弟结点的第一个键值，而是兄弟结点第一个子结点的第一个元素的值
        m_Keys[this->m_Count] = pNode->GetPointer(1)->GetElement(1);
        // 最后一个子结点为兄弟结点的第一个子结点
        m_Pointers[this->m_Count + 1] = pNode->GetPointer(1);
       
        // 修改兄弟结点
        for (i = 1; i < pNode->GetCount() - 1; i++)
        {
            pNode->SetElement(i, pNode->GetElement(i + 1),INVALID);
        }
        for (j = 1; j < pNode->GetCount(); j++)
        {
            pNode->SetPointer(j, pNode->GetPointer(j + 1));
        }
    }

    // 设置数目
    this->SetCount(this->GetCount() + 1);
    pNode->SetCount(pNode->GetCount() - 1);

    return true;
}

// 清除叶子结点中的数据
template <class DATA_TYPE>
CLeafNode<DATA_TYPE>::CLeafNode()
{
    this->m_Type = NODE_TYPE_LEAF;

    for (int i = 0; i < MAXNUM_DATA; i++)
    {
        m_Datas[i] = INVALID;
        U_Data[i] = INVALID;
    }

    m_pPrevNode = NULL;
    m_pNextNode = NULL;
}
template <class DATA_TYPE>
CLeafNode<DATA_TYPE>::~CLeafNode()
{

}

// 在叶子结点中插入数据
template <class DATA_TYPE>
bool CLeafNode<DATA_TYPE>::Insert(KEY_TYPE value,DATA_TYPE data)
{
    int i,j;
    // 如果叶子结点已满，直接返回失败
    if (GetCount() >= MAXNUM_DATA)
    {
        return false;
    }

    // 找到要插入数据的位置
    for (i = 0; (value > m_Datas[i]) && ( i < this->m_Count); i++)
    {
    }

    // 当前位置及其后面的数据依次后移，空出当前位置
    for (j = this->m_Count; j > i; j--)
    {
        m_Datas[j] = m_Datas[j - 1];
        U_Data[j] = U_Data[j - 1];
    }

    // 把数据存入当前位置
    m_Datas[i] = value;
    U_Data[i] = data;
    this->m_Count++;

    // 返回成功
    return true;
}
template <class DATA_TYPE>
bool CLeafNode<DATA_TYPE>::Delete(KEY_TYPE value)
{
    int i,j;
    bool found = false;
    for (i = 0; i < this->m_Count; i++)
    {
        if (value == m_Datas[i])
        {
            found = true;
            break;
        }
    }
    // 如果没有找到，返回失败
    if (false == found)
    {
        return false;
    }

    // 后面的数据依次前移
    for (j = i; j < this->m_Count - 1; j++)
    {
        m_Datas[j] = m_Datas[j + 1];
        U_Data[j] = U_Data[j + 1];
    }

    m_Datas[j] = INVALID;
    U_Data[j] = INVALID;
    this->m_Count--;

    // 返回成功
    return true;

}

// 分裂叶子结点，把本叶子结点的后一半数据剪切到指定的叶子结点中
template <class DATA_TYPE>
KEY_TYPE CLeafNode<DATA_TYPE>::Split(CNode<DATA_TYPE>* pNode)    
{
    // 把本叶子结点的后一半数据移到指定的结点中
    int j = 0;
    for (int i = ORDER_V + 1; i <= MAXNUM_DATA; i++)
    {
        j++;
        pNode->SetElement(j, this->GetElement(i),this->GetData(i));
        this->SetElement(i, INVALID,INVALID);
    }
    // 设置好Count个数
    this->SetCount(this->GetCount() - j);
    pNode->SetCount(pNode->GetCount() + j);

    // 返回新结点的第一个元素作为键
    return pNode->GetElement(1);
}

// 结合结点，把指定叶子结点的数据全部剪切到本叶子结点
template <class DATA_TYPE>
bool CLeafNode<DATA_TYPE>::Combine(CNode<DATA_TYPE>* pNode)
{
    // 参数检查
    if (this->GetCount() + pNode->GetCount() > MAXNUM_DATA)
    {
        return false;
    }
   
    for (int i = 1; i <= pNode->GetCount(); i++)
    {
        this->Insert(pNode->GetElement(i), pNode->GetData(i));
    }

    return true;
}
template <class DATA_TYPE>
BPlusTree<DATA_TYPE>::BPlusTree()
{
    m_Depth = 0;
    m_Root = NULL;
    m_pLeafHead = NULL;
    m_pLeafTail = NULL;
}
template <class DATA_TYPE>
BPlusTree<DATA_TYPE>::~BPlusTree()
{
    ClearTree();
}

template <class DATA_TYPE>
DATA_TYPE BPlusTree<DATA_TYPE>::Search_data(KEY_TYPE key){
    int i = 0;


    CNode<DATA_TYPE> * pNode = GetRoot();
    // 循环查找对应的叶子结点
    while (NULL != pNode)
    {        
        // 结点为叶子结点，循环结束
        if (NODE_TYPE_LEAF == pNode->GetType())
        {
            break;
        }
        // 找到第一个键值大于等于key的位置
        for (i = 1; (key >= pNode->GetElement(i) )&& (i <= pNode->GetCount()); i++)
        {
        }


        pNode = pNode->GetPointer(i);
    }

    // 没找到
    if (NULL == pNode)
    {
        return INVALID;
    }

    // 在叶子结点中继续找
   DATA_TYPE found=INVALID;
    for (i = 1; (i <= pNode->GetCount()); i++)
    {
        if (key == pNode->GetElement(i))
        {
            found = pNode->GetData(i);
        }
    }
    return found;
}

// 在树中查找数据
template <class DATA_TYPE>
bool BPlusTree<DATA_TYPE>::Search(KEY_TYPE data, char* sPath)
{
    int i = 0;
    int offset = 0;
    if (NULL != sPath)
    {
        (void)sprintf(sPath+offset, "The serach path is:");
        offset+=19;
    }

    CNode<DATA_TYPE> * pNode = GetRoot();
    // 循环查找对应的叶子结点
    while (NULL != pNode)
    {        
        // 结点为叶子结点，循环结束
        if (NODE_TYPE_LEAF == pNode->GetType())
        {
            break;
        }

        // 找到第一个键值大于等于key的位置
        for (i = 1; (data >= pNode->GetElement(i) )&& (i <= pNode->GetCount()); i++)
        {
        }

        if (NULL != sPath)
        {
            (void)sprintf(sPath+offset, " %3d -->", pNode->GetElement(1));
            offset+=8;
        }

        pNode = pNode->GetPointer(i);
    }

    // 没找到
    if (NULL == pNode)
    {
        return false;
    }

    if (NULL != sPath)
    {
        (void)sprintf(sPath+offset, "%3d", pNode->GetElement(1));
        offset+=3;
    }

    // 在叶子结点中继续找
    bool found = false;
    for (i = 1; (i <= pNode->GetCount()); i++)
    {
        if (data == pNode->GetElement(i))
        {
            found = true;
        }
    }


    if (NULL != sPath)
    {
        if (true == found)
        {

            (void)sprintf(sPath+offset, " ,successed.");
        }
        else
        {
            (void)sprintf(sPath+offset, " ,failed.");
        }
    }

    return found;
}

/* 在B+树中插入数据
插入数据首先要找到理论上要插入的叶子结点，然后分三种情况：
(1) 叶子结点未满。直接在该结点中插入即可；
(2) 叶子结点已满，且无父结点(即根结点是叶子结点)，需要首先把叶子结点分裂，然后选择插入原结点或新结点，然后新生成根节点；
(3) 叶子结点已满，但其父结点未满。需要首先把叶子结点分裂，然后选择插入原结点或新结点，再修改父结点的指针；
(4) 叶子结点已满，且其父结点已满。需要首先把叶子结点分裂，然后选择插入原结点或新结点，接着把父结点分裂，再修改祖父结点的指针。
    因为祖父结点也可能满，所以可能需要一直递归到未满的祖先结点为止。
*/
template <class DATA_TYPE>
bool BPlusTree<DATA_TYPE>::Insert(KEY_TYPE data,DATA_TYPE value)  //
{
    // 检查是否重复插入
    bool found = Search(data, NULL);
    if (true == found)
    {
        return false;
    }
    // for debug
    //if (289 == data)
    //{
    //    printf("\n%d,check failed!",data);
    //}

    // 查找理想的叶子结点
    CLeafNode<DATA_TYPE>* pOldNode = SearchLeafNode(data);
    // 如果没有找到，说明整个树是空的，生成根结点
    if (NULL == pOldNode)
    {
        pOldNode = new CLeafNode<DATA_TYPE>;
     m_pLeafHead = pOldNode;   
        m_pLeafTail = pOldNode;
        SetRoot(pOldNode);
    }

    // 叶子结点未满，对应情况1，直接插入
    if (pOldNode->GetCount() < MAXNUM_DATA)
    {
        return pOldNode->Insert(data, value);
    }

    // 原叶子结点已满，新建叶子结点，并把原结点后一半数据剪切到新结点
    CLeafNode<DATA_TYPE>* pNewNode = new CLeafNode<DATA_TYPE>;
    KEY_TYPE key = INVALID;
    key = pOldNode->Split(pNewNode);   

    // 在双向链表中插入结点
    CLeafNode<DATA_TYPE>* pOldNext = pOldNode->m_pNextNode;
    pOldNode->m_pNextNode = pNewNode;
    pNewNode->m_pNextNode = pOldNext;
    pNewNode->m_pPrevNode = pOldNode;
    if (NULL == pOldNext)
    {
        m_pLeafTail = pNewNode;
    }
    else
    {
        pOldNext->m_pPrevNode = pNewNode;
    }


    // 判断是插入到原结点还是新结点中，确保是按数据值排序的
    if (data < key)
    {
        pOldNode->Insert(data,value);    // 插入原结点
    }
    else
    {
        pNewNode->Insert(data,value);    // 插入新结点
    }

    // 父结点
    CInternalNode<DATA_TYPE>* pFather = (CInternalNode<DATA_TYPE>*)(pOldNode->GetFather());

    // 如果原结点是根节点，对应情况2
    if (NULL == pFather)
    {
        CNode<DATA_TYPE>* pNode1 = new CInternalNode<DATA_TYPE>;
        pNode1->SetPointer(1, pOldNode);                           // 指针1指向原结点
        pNode1->SetElement(1, key,value);                                // 设置键
        pNode1->SetPointer(2, pNewNode);                           // 指针2指向新结点
        pOldNode->SetFather(pNode1);                               // 指定父结点
        pNewNode->SetFather(pNode1);                               // 指定父结点
        pNode1->SetCount(1);

        SetRoot(pNode1);                                           // 指定新的根结点
        return true;
    }

    // 情况3和情况4在这里实现
    bool ret = InsertInternalNode(pFather, key, pNewNode);
    return ret;
}

/* 删除某数据
删除数据的算法如下：
(1) 如果删除后叶子结点填充度仍>=50%，只需要修改叶子结点，如果删除的是父结点的键，父结点也要相应修改；
(2) 如果删除后叶子结点填充度<50%，需要先找到一个最近的兄弟结点(左右均可)，然后分两种情况：
    A. 如果该兄弟结点填充度>50%，把该兄弟结点的最近一个数据剪切到本结点，父结点的键值也要相应修改。
    B. 如果该兄弟结点的填充度=50%，则把两个结点合并，父结点键也相应合并。(如果合并后父结点的填充度<50%，则需要递归)
*/
template <class DATA_TYPE>
bool BPlusTree<DATA_TYPE>::Delete(KEY_TYPE data)
{
    // 查找理想的叶子结点
    CLeafNode<DATA_TYPE>* pOldNode = SearchLeafNode(data);
    // 如果没有找到，返回失败
    if (NULL == pOldNode)
    {
        return false;
    }

    // 删除数据，如果失败一定是没有找到，直接返回失败
    bool success = pOldNode->Delete(data);
    if (false == success)
    {
        return false;
    }

    // 获取父结点
    CInternalNode<DATA_TYPE>* pFather = (CInternalNode<DATA_TYPE>*)(pOldNode->GetFather());
    if (NULL == pFather)
    {
        // 如果一个数据都没有了，删除根结点(只有根节点可能出现此情况)
        if (0 == pOldNode->GetCount())
        {
            delete pOldNode;
            m_pLeafHead = NULL;
            m_pLeafTail = NULL;
            SetRoot(NULL);
        }

        return true;
    }

   
    // 删除后叶子结点填充度仍>=50%，对应情况1
    if (pOldNode->GetCount() >= ORDER_V)
    {
        for (int i = 1; (data >= pFather->GetElement(i)) && (i <= pFather->GetCount()); i++)
        {
            // 如果删除的是父结点的键值，需要更改该键
            if (pFather->GetElement(i) == data)
            {
                pFather->SetElement(i, pOldNode->GetElement(1),INVALID);    // 更改为叶子结点新的第一个元素
            }
        }

        return true;
    }

    // 找到一个最近的兄弟结点(根据B+树的定义，除了叶子结点，总是能找到的)
    int flag = FLAG_LEFT;
    CLeafNode<DATA_TYPE>* pBrother = (CLeafNode<DATA_TYPE>*)(pOldNode->GetBrother(flag));

    // 兄弟结点填充度>50%，对应情况2A
    KEY_TYPE NewData = INVALID;
    DATA_TYPE NewValue = INVALID;
    if (pBrother->GetCount() > ORDER_V)
    {
        if (FLAG_LEFT == flag)    // 兄弟在左边，移最后一个数据过来
        {
            NewData = pBrother->GetElement(pBrother->GetCount());
            NewValue = pBrother->GetData(pBrother->GetCount());
        }
        else    // 兄弟在右边，移第一个数据过来
        {
            NewData = pBrother->GetElement(1);
            NewValue = pBrother->GetData(1);
        }

        pOldNode->Insert(NewData, NewValue);
        pBrother->Delete(NewData);

        // 修改父结点的键值
        if (FLAG_LEFT == flag)
        {
            for (int i = 1; i <= pFather->GetCount() + 1; i++)
            {
                if (pFather->GetPointer(i) == pOldNode && i > 1)
                {
                    pFather->SetElement(i - 1 , pOldNode->GetElement(1),INVALID);    // 更改本结点对应的键
                }
            }
        }
        else
        {
            for (int i = 1; i <= pFather->GetCount() + 1; i++)
            {
                if (pFather->GetPointer(i) == pOldNode && i > 1)
                {
                    pFather->SetElement(i - 1, pOldNode->GetElement(1),INVALID);    // 更改本结点对应的键
                }
                if (pFather->GetPointer(i) == pBrother && i > 1)
                {
                    pFather->SetElement(i - 1 , pBrother->GetElement(1),INVALID);    // 更改兄弟结点对应的键
                }
            }
        }


        return true;
    }

    // 情况2B
   
    // 父结点中要删除的键
    KEY_TYPE NewKey = NULL;

    // 把本结点与兄弟结点合并，无论如何合并到数据较小的结点，这样父结点就无需修改指针
   
    if (FLAG_LEFT == flag)
    {
        (void)pBrother->Combine(pOldNode);
        NewKey = pOldNode->GetElement(1);

        CLeafNode<DATA_TYPE>* pOldNext = pOldNode->m_pNextNode;
        pBrother->m_pNextNode = pOldNext;
        // 在双向链表中删除结点
        if (NULL == pOldNext)
        {
            m_pLeafTail = pBrother;
        }
        else
        {
            pOldNext->m_pPrevNode = pBrother;
        }
        // 删除本结点
        delete pOldNode;
    }
    else
    {
        (void)pOldNode->Combine(pBrother);
        NewKey = pBrother->GetElement(1);

        CLeafNode<DATA_TYPE>* pOldNext = pBrother->m_pNextNode;
        pOldNode->m_pNextNode = pOldNext;
        // 在双向链表中删除结点
        if (NULL == pOldNext)
        {
           m_pLeafTail = pOldNode;
        }
        else
        {
            pOldNext->m_pPrevNode = pOldNode;
        }
         // 删除本结点
        delete pBrother;
    }

    return DeleteInternalNode(pFather, NewKey);
}

// 清除整个树，删除所有结点
template <class DATA_TYPE>
void BPlusTree<DATA_TYPE>::ClearTree()
{
    CNode<DATA_TYPE>* pNode = GetRoot();
    if (NULL != pNode)
    {
        pNode->DeleteChildren();
   
        delete pNode;
    }

    m_pLeafHead = NULL;
    m_pLeafTail = NULL;
    SetRoot(NULL);
}

// 旋转以重新平衡，实际上是把整个树重构一下,结果不理想，待重新考虑
template <class DATA_TYPE>
BPlusTree<DATA_TYPE>* BPlusTree<DATA_TYPE>::RotateTree()
{
    BPlusTree* pNewTree = new BPlusTree;
    int i = 0;
    CLeafNode<DATA_TYPE> * pNode = m_pLeafHead;
    while (NULL != pNode)
    {
        for (int i = 1; i <= pNode->GetCount(); i ++)
        {
            (void)pNewTree->Insert(pNode->GetElement(i), pNode->GetData(i));
        }

        pNode = pNode->m_pNextNode;
    }

    return pNewTree;
   
}
// 检查树是否满足B+树的定义
template <class DATA_TYPE>
bool BPlusTree<DATA_TYPE>::CheckTree()
{
    CLeafNode<DATA_TYPE> * pThisNode = m_pLeafHead;
    CLeafNode<DATA_TYPE> * pNextNode = NULL;
    while (NULL != pThisNode)
    {
        pNextNode = pThisNode->m_pNextNode;
        if (NULL != pNextNode)
        {
           if (pThisNode->GetElement(pThisNode->GetCount()) > pNextNode->GetElement(1))
           {
               return false;
           }
        }
        pThisNode = pNextNode;
    }
       
    return CheckNode(GetRoot());
}

// 递归检查结点及其子树是否满足B+树的定义
template <class DATA_TYPE>
bool BPlusTree<DATA_TYPE>::CheckNode(CNode<DATA_TYPE>* pNode)
{
    if (NULL == pNode)
    {
        return true;
    }
   
    int i = 0;
    bool ret = false;
   
    // 检查是否满足50%的填充度
    if ((pNode->GetCount() < ORDER_V) && (pNode != GetRoot()))
   {
        return false;
    }

    // 检查键或数据是否按大小排序
    for (i = 1; i < pNode->GetCount(); i++)
    {
        if (pNode->GetElement(i) > pNode->GetElement(i + 1))
        {
            return false;
        }
    }

    if (NODE_TYPE_LEAF == pNode->GetType())
    {
        return true;
    }

    // 对中间结点，递归检查子树
    for (i = 1; i <= pNode->GetCount() + 1; i++)
    {
        ret = CheckNode(pNode->GetPointer(i));
     // 只要有一个不合法就返回不合法
        if (false == ret)
        {
            return false;
        }
    }

    return true;

}

// 打印整个树
template <class DATA_TYPE>
void BPlusTree<DATA_TYPE>::PrintTree()
{
    CNode<DATA_TYPE>* pRoot = GetRoot();
    if (NULL == pRoot) return;

    CNode<DATA_TYPE>* p1, *p2, *p3;
    int i, j, k;
    int total = 0;

    printf("\n第一层\n | ");
    PrintNode(pRoot);
    total = 0;
    printf("\n第二层\n | ");
    for (i = 1; i <= MAXNUM_POINTER; i++)
    {
        p1 = pRoot->GetPointer(i);
        if (NULL == p1) continue;
        PrintNode(p1);
        total++;
        if (total%4 == 0) printf("\n | ");
    }
    total = 0;
    printf("\n第三层\n | ");
    for (i = 1; i <= MAXNUM_POINTER; i++)
    {
        p1 = pRoot->GetPointer(i);
        if (NULL == p1) continue;
        for (j = 1; j <= MAXNUM_POINTER; j++)
        {
            p2 = p1->GetPointer(j);
            if (NULL == p2) continue;
            PrintNode(p2);
            total++;
            if (total%4 == 0) printf("\n | ");
        }
    }
    total = 0;
    printf("\n第四层\n | ");
    for (i = 1; i <= MAXNUM_POINTER; i++)
    {
        p1 = pRoot->GetPointer(i);
        if (NULL == p1) continue;
        for (j = 1; j <= MAXNUM_POINTER; j++)
        {
            p2 = p1->GetPointer(j);
            if (NULL == p2) continue;
            for (k = 1; k <= MAXNUM_POINTER; k++)
            {
                p3 = p2->GetPointer(k);
                if (NULL == p3) continue;
                PrintNode(p3);
                total++;
                if (total%4 == 0) printf("\n | ");
            }
        }
    }
}

// 打印某结点
template <class DATA_TYPE>
void BPlusTree<DATA_TYPE>::PrintNode(CNode<DATA_TYPE>* pNode)
{
    if (NULL == pNode)
    {
        return;
    }
   
    for (int i = 1; i <= MAXNUM_KEY; i++)
    {
        printf("%3d ", pNode->GetElement(i));
        if (i >= MAXNUM_KEY)
        {
            printf(" | ");
        }
    }
}

// 查找对应的叶子结点
template <class DATA_TYPE>
CLeafNode<DATA_TYPE>* BPlusTree<DATA_TYPE>::SearchLeafNode(KEY_TYPE data)
{
    int i = 0;

    CNode <DATA_TYPE>* pNode = GetRoot();
    // 循环查找对应的叶子结点
    while (NULL != pNode)
    {        
        // 结点为叶子结点，循环结束
        if (NODE_TYPE_LEAF == pNode->GetType())
        {
            break;
        }

        // 找到第一个键值大于等于key的位置
        for (i = 1; i <= pNode->GetCount(); i++)
        {
            if (data < pNode->GetElement(i))
            {
                break;
            }
        }

        pNode = pNode->GetPointer(i);
    }

    return (CLeafNode<DATA_TYPE>*)pNode;
}

//递归函数：插入键到中间结点
template <class DATA_TYPE>
bool BPlusTree<DATA_TYPE>::InsertInternalNode(CInternalNode<DATA_TYPE>* pNode, KEY_TYPE key, CNode<DATA_TYPE>* pRightSon)
{
    if (NULL == pNode || NODE_TYPE_LEAF ==pNode->GetType())
    {
        return false;
    }

    // 结点未满，直接插入
    if (pNode->GetCount() < MAXNUM_KEY)
    {
        return pNode->Insert(key, pRightSon,NULL);
    }

    CInternalNode<DATA_TYPE>* pBrother = new CInternalNode<DATA_TYPE>;  //C++中new 类名表示分配一个类需要的内存空间，并返回其首地址；
    KEY_TYPE NewKey = INVALID;
    // 分裂本结点
    NewKey = pNode->Split(pBrother, key);   

    if (pNode->GetCount() < pBrother->GetCount())
    {
        pNode->Insert(key, pRightSon,NULL);
    }
    else if (pNode->GetCount() > pBrother->GetCount())
    {
         pBrother->Insert(key, pRightSon,NULL);
    }
    else    // 两者相等，即键值在第V和V+1个键值中间的情况，把字节点挂到新结点的第一个指针上
    {
        pBrother->SetPointer(1,pRightSon);
        pRightSon->SetFather(pBrother);
    }

    CInternalNode<DATA_TYPE>* pFather = (CInternalNode<DATA_TYPE>*)(pNode->GetFather());
    // 直到根结点都满了，新生成根结点
    if (NULL == pFather)
    {
        pFather = new CInternalNode<DATA_TYPE>;
        pFather->SetPointer(1, pNode);                           // 指针1指向原结点
        pFather->SetElement(1, NewKey,INVALID);                          // 设置键
        pFather->SetPointer(2, pBrother);                        // 指针2指向新结点
        pNode->SetFather(pFather);                               // 指定父结点
        pBrother->SetFather(pFather);                            // 指定父结点
        pFather->SetCount(1);

        SetRoot(pFather);                                        // 指定新的根结点
        return true;
    }

    // 递归
    return InsertInternalNode(pFather, NewKey, pBrother);
}

// 递归函数：在中间结点中删除键
template <class DATA_TYPE>
bool BPlusTree<DATA_TYPE>::DeleteInternalNode(CInternalNode<DATA_TYPE>* pNode, KEY_TYPE key)
{
    // 删除键，如果失败一定是没有找到，直接返回失败
    bool success = pNode->Delete(key);
    if (false == success)
    {
        return false;
    }

    // 获取父结点
    CInternalNode<DATA_TYPE>* pFather = (CInternalNode<DATA_TYPE>*)(pNode->GetFather());
    if (NULL == pFather)
    {
        // 如果一个数据都没有了，把根结点的第一个结点作为根结点
        if (0 == pNode->GetCount())
        {
            SetRoot(pNode->GetPointer(1));
            delete pNode;
        }

        return true;
    }
   
    // 删除后结点填充度仍>=50%
    if (pNode->GetCount() >= ORDER_V)
    {
        for (int i = 1; (key >= pFather->GetElement(i)) && (i <= pFather->GetCount()); i++)
        {
            // 如果删除的是父结点的键值，需要更改该键
            if (pFather->GetElement(i) == key)
            {
                pFather->SetElement(i, pNode->GetElement(1),INVALID);    // 更改为叶子结点新的第一个元素
            }
        }

        return true;
    }

    //找到一个最近的兄弟结点(根据B+树的定义，除了根结点，总是能找到的)
    int flag = FLAG_LEFT;
    CInternalNode<DATA_TYPE>* pBrother = (CInternalNode<DATA_TYPE>*)(pNode->GetBrother(flag));

    // 兄弟结点填充度>50%
    KEY_TYPE NewData = INVALID;
    if (pBrother->GetCount() > ORDER_V)
    {
        pNode->MoveOneElement(pBrother);

        // 修改父结点的键值
        if (FLAG_LEFT == flag)
        {
            for (int i = 1; i <= pFather->GetCount() + 1; i++)
            {
                if (pFather->GetPointer(i) == pNode && i > 1)
                {
                    pFather->SetElement(i - 1 , pNode->GetElement(1),INVALID);    // 更改本结点对应的键
                }
            }
        }
        else
        {
            for (int i = 1; i <= pFather->GetCount() + 1; i++)
            {
                if (pFather->GetPointer(i) == pNode && i > 1)
                {
                    pFather->SetElement(i - 1, pNode->GetElement(1),INVALID);    // 更改本结点对应的键
                }
                if (pFather->GetPointer(i) == pBrother && i > 1)
                {
                    pFather->SetElement(i - 1 , pBrother->GetElement(1),INVALID);    // 更改兄弟结点对应的键
                }
            }
        }

        return true;
    }
   
    // 父结点中要删除的键：兄弟结点都不大于50，则需要合并结点，此时父结点需要删除键
    KEY_TYPE NewKey = NULL;

    // 把本结点与兄弟结点合并，无论如何合并到数据较小的结点，这样父结点就无需修改指针
    if (FLAG_LEFT == flag)
    {
        (void)pBrother->Combine(pNode);
        NewKey = pNode->GetElement(1);
        delete pNode;
    }
    else
    {
        (void)pNode->Combine(pBrother);
        NewKey = pBrother->GetElement(1);
        delete pBrother;
    }

    // 递归
    return DeleteInternalNode(pFather, NewKey);
}

