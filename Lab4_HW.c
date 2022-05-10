#define prvInsertBlockIntoFreeList(pxBlockToInsert)                                                                                \
    {                                                                                                                              \
        BlockLink_t *pxIterator, *pxPrevious, *pxBlock;                                                                            \
        size_t xBlockSize;                                                                                                         \
        pxBlock = pxBlockToInsert;                                                                                                 \
                                                                                                                                   \
        /* TODO: Merge free blocks                                                    */                                           \
        /*                                                                            */                                           \
        /* HINT                                                                       */                                           \
        /* 1. You may need to use the `pxPrevious` pointer to keep trace of the       */                                           \
        /*    previous block.                                                         */                                           \
        /* 2. Because it is a macro, use `pxBlock` instead of `pxBlockToInsert`       */                                           \
        /*    below, or you may encounter a problem.                                  */                                           \
        /*                                                                            */                                           \
        mergmain();                                                                                                                \
                                                                                                                                   \
        xBlockSize = pxBlock->xBlockSize;                                                                                          \
                                                                                                                                   \
        /* Iterate through the list until a block is found that has a larger size */                                               \
        /* than the block we are inserting. */                                                                                     \
        for (pxIterator = &xStart; pxIterator->pxNextFreeBlock->xBlockSize < xBlockSize; pxIterator = pxIterator->pxNextFreeBlock) \
        {                                                                                                                          \
            /* There is nothing to do here - just iterate to the correct position. */                                              \
        }                                                                                                                          \
                                                                                                                                   \
        /* Update the list to include the block being inserted in the correct */                                                   \
        /* position. */                                                                                                            \
        pxBlock->pxNextFreeBlock = pxIterator->pxNextFreeBlock;                                                                    \
        pxIterator->pxNextFreeBlock = pxBlock;                                                                                     \
    }                                                                                                                              \
    int mergelist(BlockLink_t *pxBlock)                                                                                            \
    {
char data[80];
BlockLink_t *pxPrevious, *Start;
Start = xStart.pxNextFreeBlock;
//pxPrevious = &xStart;
int i = 0;
int ii = 1;
if (Start == pxBlock)
{
    ii = 0;
    i = 1;
}
else
{
    while (Start != &xEnd)
    {
        if (Start->pxNextFreeBlock == pxBlock)
        {
            ii = 0;

            break;
        }
        pxPrevious = Start->pxNextFreeBlock;
        Start = Start->pxNextFreeBlock;
    }
}
Start = xStart.pxNextFreeBlock;

while (Start != &xEnd)
{
    if (pxBlock == Start + (1 * Start->xBlockSize / 8))
    {
        if (xStart.pxNextFreeBlock == pxBlock)
        {
            Start->xBlockSize += pxBlock->xBlockSize;
            xStart.pxNextFreeBlock = (pxBlock)->pxNextFreeBlock;
            //return 0;
        }
        else
        {
            pxPrevious->pxNextFreeBlock = pxPrevious->pxNextFreeBlock->pxNextFreeBlock;
            Start->xBlockSize += pxBlock->xBlockSize;
            //return 0;
        }
    }
    Start = Start->pxNextFreeBlock;
}
return 1;
}

int mergelist(BlockLink_t *pxBlock)
{
    char data[80];
    BlockLink_t *pxPrevious, *Start;
    Start = xStart.pxNextFreeBlock;
    //pxPrevious = &xStart;
    int i = 0;
    int ii = 1;
    if (Start == pxBlock) //找目標的前一項
    {
        ii = 0;
        i = 1;
    }
    else
    {
        while (Start != &xEnd)
        {
            if (Start->pxNextFreeBlock == pxBlock)
            {
                ii = 0;

                break;
            }
            pxPrevious = Start->pxNextFreeBlock;
            Start = Start->pxNextFreeBlock;
        }
    }
    Start = xStart.pxNextFreeBlock;

    while (Start != &xEnd)
    {
        if (pxBlock == Start + (1 * Start->xBlockSize / 8)) //如果目標跟end address相同則進行變換
        {
            if (xStart.pxNextFreeBlock == pxBlock)
            {
                Start->xBlockSize += pxBlock->xBlockSize;
                xStart.pxNextFreeBlock = (pxBlock)->pxNextFreeBlock;
                //return 0;
            }
            else
            {
                pxPrevious->pxNextFreeBlock = pxPrevious->pxNextFreeBlock->pxNextFreeBlock;
                Start->xBlockSize += pxBlock->xBlockSize;
                //return 0;
            }
        }
        Start = Start->pxNextFreeBlock;
    }
    return 1;
}

void mergemain() //從頭到尾掃一遍
{
    BlockLink_t *Start = xStart.pxNextFreeBlock;
    while (Start != &xEnd)
    {
        int i = mergelist(Start);
        if (i)
        {
            Start = Start->pxNextFreeBlock;
        }
        else
        {
            Start = xStart.pxNextFreeBlock;
        }
    }
}

void vPrintFreeList(void)
{
    //mergemain();
    BlockLink_t *Start = xStart.pxNextFreeBlock;
    BlockLink_t End = xEnd;
    int a = 16;
    char data[80];
    sprintf(data, "StartAddress heapSTRUCT_SIZE xBlockSize EndAddress\n\r");
    HAL_UART_Transmit(&huart2, (uint8_t *)data, strlen(data), 0xffff);
    //sprintf(data, "%p         %d           %4d         %p\n\r",&xStart,heapSTRUCT_SIZE,xStart.xBlockSize,xStart.pxNextFreeBlock);
    //HAL_UART_Transmit(&huart2, (uint8_t *)data, strlen(data), 0xffff);
    while (Start != &xEnd)
    {
        sprintf(data, "%p         %d           %4d         %p   %d\n\r", Start, heapSTRUCT_SIZE, Start->xBlockSize, Start + (1 * Start->xBlockSize / 8), xStart.pxNextFreeBlock == Start + (1 * Start->xBlockSize / 8));

        Start = Start->pxNextFreeBlock;
        HAL_UART_Transmit(&huart2, (uint8_t *)data, strlen(data), 0xffff);
    }
    sprintf(data, "configADJUSTED_HEAP_SIZE: %0d xFreeBytesRemaining: %0d\n\r", configADJUSTED_HEAP_SIZE, xFreeBytesRemaining);
    HAL_UART_Transmit(&huart2, (uint8_t *)data, strlen(data), 0xffff);
    //mergemain();
    /* TODO: implement this function
     *
     * Reference format
     * > sprintf(data, "StartAddress heapSTRUCT_SIZE xBlockSize EndAddress\n\r");
     * > sprintf(data, "%p         %d           %4d         %p\n\r", ...);
     * > sprintf(data, "configADJUSTED_HEAP_SIZE: %0d xFreeBytesRemaining: %0d\n\r", ...);
     */
}