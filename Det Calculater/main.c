//
//  main.c
//  Det Calculater
//
//  Created by DarXs微分 on 2020/10/16.
//

#include <stdio.h>
#define N 10                                    //输入你想要的最高阶数


int mi( int a ){            //定义函数 "mi" ，求-1的 a 次幂
    
    int b = 1 ;             //初始化为1
    
    if( a % 2 == 1 ){       //如果 a 为奇数则将b改为-1
        b = -1 ;
    }
    
    return b ;              //不用 "pow" 的原因是：它要求底数和幂都是 double 类型
}                           //预计会出现不确定位数，而且幂函数要求底数大于 0


long long det( int *p, int n ){                 //定义求行列式的函数
    
    long long x = 0 ;                           //定义输出结果 x
    int i , j , k ;                             //定义计数变量 i , j , k
    int b[n-1][n-1] ;                               //定义用来储存 余子式 的二维数组 b[N][N]
    
    int *q = &b[0][0] ;                         //定义指向 余子式 首项的指针 *q
    
    for( i=0 ; i<=n-2 ; i++ ){
        for( j=0 ; j<=n-2 ; j++ ){              //从 0 到 n-1 循环计数变量 i , j（作为 余子式 的行和列）
            
            if( i==j ){
                b[j][i] = 1 ;                   //初始化二维数组 b[N][N]（矩阵）为
            }                                   //仅有主对角线上有数字
            else{                               //且为都 1 的单位矩阵（E）
                b[j][i] = 0 ;
            }
            
        }
    }
    
    if( n==1 ){                                 //给出一阶行列式的值（就是该数组的首项）
        x = *p ;
    }
    else{                                       //给出 N 阶行列式的递归定义：
        for( i=0 ; i<=n-1 ; i++ ){              //「第一行 第(i+1)列 的元素」*「与之对应的余子式」*「(-1) 的 ((i+1)+1)次幂」
                                                //将所有上述乘积求和 就是该行列式的最终结果；其中余子式用到了 (N-1) 阶行列式的算法
            for( j=0 ; j<=n-2 ; j++ ){
                for( k=0 ; k<=n-2 ; k++ ){      //这两个循环在将 余子式 赋值到 二维数组 b[N][N]（矩阵）上
                    
                    if(k>=i){
                        b[j][k] = *( p + (j+1)*N + (k+1) ) ;        //(i+1)列及之后的对应元素 赋值时要读取其右侧一行
                    }
                    else{
                        b[j][k] = *( p + (j+1)*N + k ) ;            //(i+1)列之前的对应元素 赋值时直接读取其对应行
                    }
                                                                    //讲一下这里 指针指向数组的用法：
                }                                                   //由于数组在内存中成一维线性排列，要读取 a[j][k] 就要用
            }                                                       // *( p + j*N + k ) 其中 N 为数组的第一维数量
            
            x += *( p + i ) * mi(i) * det(q,n-1) ;                  //输出结果为这些乘积的和（ x 在此作为累加器）
                                                                    //这个函数的递归思想就体现在 「通过自己调用自己；来求余子式」 上
        }
    }
    
    return x ;                                                      //将求和之后的最终结果作为函数的返回值
}


int main(int argc, const char * argv[]){                            //最后给出 用户可视界面 的主函数 的定义
    
    int n = N ;                                                     //定义 n 用来储存行列式阶数
    int a[N][N] ;                                                   //定义二维数组 a[N][N] 用来储存用户输入的行列式
    int i , j ;                                                     //定义计数变量 i , j
    
    int *p = &a[0][0] ;                                             //定义指向 行列式 首项的指针 *p
    
    for( i=0 ; i<=n-1 ; i++ ){                                      //此后同上，初始化矩阵
        for( j=0 ; j<=n-1 ; j++ ){
                                                    //从 0 到 n-1 循环计数变量 i , j（作为 行列式 的行和列）
            if( i==j ){
                a[j][i]= 1 ;                        //初始化二维数组 a[N][N]（矩阵）为
            }                                       //仅有主对角线上有数字
            else{                                   //且为都 1 的单位矩阵（E）
                a[j][i]= 0 ;
            }
            
        }
    }
                                                                    //接下来是用户界面提示 和 获取行列式阶数
    printf ( "这是Dr.Xiong的整数行列式计算器\n" ) ;
    printf ( "请输入行列式阶数：(<=%d阶)\n" , N ) ;
    scanf ( "%d" , &n ) ;
    printf ( "请输入该%d阶行列式\n" , n ) ;
    
    for( i=0 ; i<=n-1 ; i++ ){
        for( j=0 ; j<=n-1 ; j++ ){                                  //这两个循环在将 行列式 赋值到 二维数组 a[N][N] 上
            
            scanf ( "%d" , &a[j][i] ) ;
            
        }
    }
    
    printf ( "计算结果是：\n%lld\n" , det(p,n) ) ;                    //打印出结果
    
    return 0 ;                                                      //全剧终；感谢阅读，欢迎交流
}
