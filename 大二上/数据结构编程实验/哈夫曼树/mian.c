#include<stdio.h>
#include<string.h>
#define MAX 128
struct huffmanNode{
    char c;
    int w,tag,left,right;
}node[MAX*2+10]={0};
int cnt=0,ch[MAX]={0};
int main(){
    // 数据初始化：
    char str[1000],k;
    int i=0,j,temp;
    printf("give your string:\n");
    scanf("%s",str);
    while(str[i])  ch[(int)str[i++]]++;
    for(i=0;i<MAX;i++){
        if(ch[i]!=0){
            node[cnt].c=(char)(i);
            node[cnt].w=ch[i];
            node[cnt++].tag=0;
        }
    }
    // 构建霍夫曼树
    int min1,min2,x1,x2;
    for(i=0;i<cnt-1;i++){
        min1=0xffff;min2=0xffff;
        x1=-1;x2=-1;
        for(j=0;j<cnt+i;j++){
            if(node[j].w<min1&&node[j].tag==0){
                min2=min1;x2=x1;
                min1=node[j].w;x1=j;
            }
            else if(node[j].w<min2&&node[j].tag==0){
                min2=node[j].w;x2=j;
            }
        }
        node[x1].tag=1;node[x2].tag=1;
        node[cnt+i].w=min1+min2;
        node[cnt+i].left=x1;node[cnt+i].right=x2;// 在此霍夫曼树中，树的右节点的权值大一些。
        node[cnt+i].tag=0;
    }
    printf("input 0 and 1, and Enter after each number.\nand input q to quit:\n");
    // 解码：
    k=getchar();
    while(k!='q'){
        temp=2*cnt-2;
        while(k!='0'&&k!='1'&& k!='q')k=getchar();
        while(temp>=cnt){
            if(k=='1'){
                temp=node[temp].right;
            }
            else if(k=='0'){
                temp=node[temp].left;
            }
            else if(k=='q'){
                break;
            }
            k = getchar();
        }
        if(k!='q')
            printf("%c\n\n",node[temp].c);
    }
    return 0;
}
