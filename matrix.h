#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "loadData.h"
#include <fstream>
#include <sstream>
#include <stack>
#define MAX 1000000
#define MIN -100000
#define MAX_MATRIX_COL 1000
#define MAX_MATRIX_ROW 100
using namespace std;
class Matrix
{
public:
    double **mat;
    int col,row;
public:
    int loadMatrix(Matrix *matrix,dataToMatrix dtm)
    {
        int i,j;
        Data *p;
        p=dtm.dataSet->next;
        matrix->mat=(double **)malloc(sizeof(double*)*dtm.col);
        if(!matrix->mat)
        {
            cout<<"loadMatrix fail"<<endl;
            exit(-1);
        }
        for(i=0; i<dtm.col&&p!=NULL; i++)
        {
            matrix->mat[i]=(double *)malloc(sizeof(double)*dtm.row);
            if(!matrix->mat[i])
            {
                cout<<"loadmatrix fail"<<endl;
                exit(-1);
            }
            for(j=0; j<dtm.row; j++)
            {
                //matrix->mat[i][j]=p->attr_string[j];
            }
            p=p->next;
        }
        matrix->row=dtm.row;
        matrix->col=dtm.col;
        return 0;
    }

    /**
    new��malloc�ı����������ڣ�ǰ������Զ�����ԣ������ǻ������ͻ��������ͣ��ṹ�����Ͷ����Կ�������
    ʹ��new�ǻ���ö���Ĺ��캯������ʼ�����󣬼����ȵ÷����ڴ棬���ʼ���������ڴ������ڲ�ʵ�ֿ����ǵ���malloc
    ��mallocֻ�Ƿ����ڴ棬���ڻ������Ͷ��ԣ�����û����ģ����ڿ��Լ�����ʼ���������ڶ�����ԣ�mallocֻ�����ڴ�
    �����ù��캯�������Բ���Զ�����г�ʼ��
    **/

    int initMatrix(Matrix *matrix,int col,int row)
    {
        initMatrix(matrix,col,row,0);
    }
    int initMatrix(Matrix *matrix,int col,int row,double lam)
    {
        if(col==0||row==0)
        {
            cout<<"matrix row or col no can 0"<<endl;
            exit(-1);
        }
        matrix->col=col;
        matrix->row=row;
        matrix->mat=new double *[col];
        if(!matrix->mat)
        {
            cout<<"initMatrix fail1"<<endl;
            exit(-1);
        }
        int i=0,j=0;
        for(i=0; i<col; i++)
        {
            matrix->mat[i]=new double[row];
            if(!matrix->mat[i])
            {
                cout<<"initMatrix fail2"<<endl;
                exit(-1);
            }
            for(j=0; j<row; j++)
            {
                matrix->mat[i][j]=0;
                if(i==j)
                    matrix->mat[i][j]=lam;
            }
        }
        return 0;
    }
    int print(Matrix matrix)
    {
        int i,j;
        for(i=0; i<matrix.col; i++)
        {
            for(j=0; j<matrix.row; j++)
            {
                cout<<matrix.mat[i][j]<<"  ";;
            }
            cout<<endl;
        }
    }
    int copy(Matrix matrixA,Matrix *matrixB)
    {
        if(!matrixB)//��Ӧ�ÿ���a
        {
            cout<<"matrixB is null"<<endl;
            exit(-1);
        }
        if(matrixB->col!=matrixA.col||matrixB->row!=matrixA.row)
        {
            cout<<"matrixA matrixB is no "<<endl;
            exit(-1);
        }
        int i,j;
        for(i=0; i<matrixA.col; i++)
        {
            for(j=0; j<matrixA.row; j++)
            {
                matrixB->mat[i][j]=matrixA.mat[i][j];
            }
        }
        return 0;
    }
    Matrix getOneRow(Matrix matrix,int iRow)
    {
        Matrix oneRow;
        oneRow.col=matrix.col;
        oneRow.row=1;
        initMatrix(&oneRow,oneRow.col,oneRow.row);
        int i=0;
        for(i=0; i<oneRow.col; i++)
        {
            oneRow.mat[i][0]=matrix.mat[i][iRow-1];
        }
        return oneRow;
    }
    Matrix getOneCol(Matrix matrix,int iCol)
    {
        Matrix oneCol;
        oneCol.row=matrix.row;
        oneCol.col=1;
        initMatrix(&oneCol,oneCol.col,oneCol.row);
        int i=0;
        for(i=0; i<oneCol.row; i++)
        {
            oneCol.mat[0][i]=matrix.mat[iCol][i];
        }
        return oneCol;
    }
    int deleteOneRow(Matrix *matrix,int iRow)
    {
        if(matrix->row==1)
        {
            cout<<"matrix is vec"<<endl;
            exit(-1);
        }
        int i,j;
        for(i=iRow; i<matrix->row; i++)
        {
            for(j=0;j<matrix->col;j++)
            {
                matrix->mat[j][i]=matrix->mat[j][i+1];
            }
        }
        matrix->row--;
        return 0;
    }
    void transposematrix(Matrix matrix,Matrix *matrixT)//������ʽ��ת��
    {
        if(matrixT->col!=matrix.row||matrixT->row!=matrix.col)
        {
            cout<<"matrix matrixT is no "<<endl;
            exit(-1);
        }
        int i=0,j=0;
        for(i=0; i<matrixT->col; i++)
        {
            for(j=0; j<matrixT->row; j++)
            {
                matrixT->mat[i][j]=matrix.mat[j][i];
            }
        }
    }
    int addmatrix(Matrix *addMatrix,Matrix matrix1,Matrix matrix2)
    {
        if(matrix1.col!=matrix2.col||matrix1.row!=matrix2.row||addMatrix->col!=matrix1.col||addMatrix->row!=matrix1.row)
        {
            cout<<"addMatrix matrix1 matrix2 is no"<<endl;
            exit(-1);
        }
        int i,j;
        for(i=0; i<matrix1.col; i++)
        {
            for(j=0; j<matrix1.row; j++)
            {
                addMatrix->mat[i][j]=matrix1.mat[i][j]+matrix2.mat[i][j];
            }
        }
        return 0;
    }

    int submatrix(Matrix *subMatrix,Matrix matrix1,Matrix matrix2)
    {
        if(matrix1.col!=matrix2.col||matrix1.row!=matrix2.row||subMatrix->col!=matrix1.col||subMatrix->row!=matrix1.row)
        {
            cout<<"subMatrix matrix1 matrix2 is no"<<endl;
            exit(-1);
        }
        int i,j;
        subMatrix->col=matrix1.col;
        subMatrix->row=matrix1.row;
        for(i=0; i<matrix1.col; i++)
        {
            for(j=0; j<matrix1.row; j++)
            {
                subMatrix->mat[i][j]=matrix1.mat[i][j]-matrix2.mat[i][j];
            }
        }
        return 0;
    }

    int multsmatrix(Matrix *multsMatrix,Matrix matrix1,Matrix matrix2)//������ʽ�����
    {
        if(matrix1.row!=matrix2.col||multsMatrix->col!=matrix1.col||multsMatrix->row!=matrix2.row)
        {
            cout<<"multsmatrix error"<<endl;
            exit(-1);
        }
        int i,j,k,l;
        for(i=0; i<matrix1.col; i++)
        {
            for(j=0; j<matrix2.row; j++)
            {
                multsMatrix->mat[i][j]=0;
            }
        }
        for(i=0; i<matrix1.col; i++)
        {
            for(j=0; j<matrix2.row; j++)
            {
                for(k=0; k<matrix1.row; k++)
                {
                    multsMatrix->mat[i][j]+=matrix1.mat[i][k]*matrix2.mat[k][j];
                }
            }
        }
        return 0;
    }
    //����ʽ
    double detmatrix(Matrix matrix)
    {
        if(matrix.col!=matrix.row)
        {
            cout<<"matrix det is no"<<endl;
            exit(-1);
        }
        Matrix matrixCopy;
        matrixCopy.initMatrix(&matrixCopy,matrix.col,matrix.row);
        matrixCopy.copy(matrix,&matrixCopy);
        double det=1;
        int i=0,j,k;
        double max=MIN;
        int swap=-1;
        double temp;
        double aij[MAX_MATRIX_COL][MAX_MATRIX_ROW];//�����þ���͸�����
        for(k=0; k<matrixCopy.row-1; k++)//k��ʾ��k����Ԫ��һ����Ҫn-1��
        {
            for(i=0; i<matrixCopy.col; i++)
            {
                if(matrixCopy.mat[i][k]>max)//ÿһ����Ԫ���ǱȽϵ�k�е�Ԫ�أ�ѡ����k��������һ��
                {
                    swap=i;
                }
            }//�ҵ���k������Ԫ��ȥ������е��±�
            if(swap==-1||matrixCopy.mat[swap][k]==0)
                return -1;//�����ԪΪ0
            for(j=0; j<matrixCopy.row; j++)
            {
                temp=matrixCopy.mat[k][j];
                matrixCopy.mat[k][j]=matrixCopy.mat[swap][j];
                matrixCopy.mat[swap][j]=temp;
            }//��k����Ԫ��ѡ������һ����swap�У����k�н���
            for(i=k+1; i<matrixCopy.col; i++)
            {
                aij[i][k]=matrixCopy.mat[i][k]/matrixCopy.mat[k][k];// ��k����Ԫ����Ԫ��Ϊ��k�е�k�У��ѵ�k�����µ��ж�������Ԫ
                for(j=k; j<matrixCopy.row; j++)//����k�����µ�ÿһ�е�ÿһ��Ԫ�ض���ȥ��������Ԫ���ӵĳ˻�
                {
                    matrixCopy.mat[i][j]-=aij[i][k]*matrixCopy.mat[k][j];
                }
            }
        }
        for(i=0; i<matrixCopy.col; i++)
        {
            det*=matrixCopy.mat[i][i];
        }
        cout<<"det="<<det<<endl;
        return det;
    }
    //��˹��Ԫ��������,�ر�ע�⣬LU�ֽⲻ�ܽ�������ʽ�任
    int nimatrix(Matrix *niMatrix,Matrix matrix)
    {
        if(matrix.col!=matrix.row)
        {
            cout<<"matrix ni is no "<<endl;
            exit(-1);
        }
        if(detmatrix(matrix)==0)//�������������ʽ����������Ԫ��ȥ�ı��˲���������δ��ݲ��ı���һ������
        {
            cout<<"matrix det is no so ni is no "<<endl;
            exit(-1);
        }
        int i=0,j,k;
        double temp;
        Matrix cpMatrix;
        Matrix uMatrix;
        Matrix lMatrix;
        Matrix uniMatrix;
        Matrix lniMatrix;
        initMatrix(&uniMatrix,matrix.col,matrix.row);
        initMatrix(&lniMatrix,matrix.col,matrix.row);
        initMatrix(&cpMatrix,matrix.col,matrix.row);
        initMatrix(&uMatrix,matrix.col,matrix.row);
        initMatrix(&lMatrix,uMatrix.col,uMatrix.row);
        copy(matrix,&cpMatrix);
        double aij[MAX_MATRIX_COL][MAX_MATRIX_ROW];
        for(k=0; k<matrix.row-1; k++)//k��ʾ��k����Ԫ��һ����Ҫn-1��
        {
            for(i=k+1; i<matrix.col; i++)
            {
                aij[i][k]=matrix.mat[i][k]/matrix.mat[k][k];// ��k����Ԫ����Ԫ��Ϊ��k�е�k�У��ѵ�k�����µ��ж�������Ԫ
                for(j=k; j<matrix.row; j++)//����k�����µ�ÿһ�е�ÿһ��Ԫ�ض���ȥ��������Ԫ���ӵĳ˻�
                {
                    matrix.mat[i][j]-=aij[i][k]*matrix.mat[k][j];
                }
            }
        }
        copy(matrix,&uMatrix);
        cout<<"uMatrix"<<endl;
        print(uMatrix);
        for(j=0; j<matrix.row; j++)
        {
            for(i=j+1; i<matrix.col; i++)
            {
                temp=0;
                for(k=0; k<j; k++)
                {
                    temp=lMatrix.mat[i][k]*uMatrix.mat[k][j];
                }
                lMatrix.mat[i][j]=1/uMatrix.mat[j][j]*(cpMatrix.mat[i][j]-temp);
            }
        }
        for(i=0; i<lMatrix.col; i++)
        {
            for(j=0; j<lMatrix.row; j++)
            {
                if(i==j)
                    lMatrix.mat[i][j]=1;
                if(j>i)
                    lMatrix.mat[i][j]=0;
            }
        }
        cout<<"lMatrix"<<endl;
        print(lMatrix);
        Matrix multsMatrix;
        multsMatrix.initMatrix(&multsMatrix,lMatrix.col,uMatrix.row);
        matrix.multsmatrix(&multsMatrix,lMatrix,uMatrix);
        cout<<"lu"<<endl;
        print(multsMatrix);
        //����u��
        for(j=0; j<uMatrix.row; j++)
        {
            for(i=j; i>=0; i--)
            {
                if(i==j)
                    uniMatrix.mat[i][j]=1/uMatrix.mat[i][j];
                else
                {
                    temp=0;
                    for(k=j; k>i; k--)
                    {
                        temp+=uMatrix.mat[i][k]*uniMatrix.mat[k][j];
                    }
                    uniMatrix.mat[i][j]=-1/uMatrix.mat[i][i]*temp;
                }
            }
        }
        cout<<"uniMatrix"<<endl;
        print(uniMatrix);
        //����l��
        for(j=0; j<lMatrix.row; j++)
        {
            for(i=0; i<lMatrix.col; i++)
            {
                if(j==i)
                    lniMatrix.mat[i][j]=1;
                else
                {
                    temp=0;
                    for(k=j; k<i; k++)
                    {
                        temp+=(lMatrix.mat[i][k]*lniMatrix.mat[k][j]);
                    }
                    lniMatrix.mat[i][j]=-temp;
                }
            }
        }
        cout<<"lniMatrix"<<endl;
        print(lniMatrix);
        multsmatrix(&multsMatrix,uniMatrix,lniMatrix);
        cout<<"luni"<<endl;
        print(multsMatrix);
        copy(multsMatrix,niMatrix);
        multsmatrix(&multsMatrix,cpMatrix,*niMatrix);
        cout<<"luluni"<<endl;
        print(multsMatrix);
        copy(cpMatrix,&matrix);
    }
    int LDL(Matrix x)//�����LDL�ֽ⣬��֪���������ھ�������ֵ�������������
    {
        Matrix l;
        l.initMatrix(&l,x.col,x.row);
        Matrix d;
        d.initMatrix(&d,x.col,x.row);
        int i,j,k;
        Matrix temp;
        temp.initMatrix(&temp,x.col,x.row);
        for(i=0;i<x.col;i++)
        {
            l.mat[i][i]=1;
            for(j=0;j<i;j++)
            {
                for(k=0;k<j;k++)
                {
                    temp.mat[i][k]=l.mat[i][k]*d.mat[k][k];
                    temp.mat[i][j]-=temp.mat[i][k]*l.mat[j][k];
                }
                temp.mat[i][j]=temp.mat[i][j]+x.mat[i][j];
                l.mat[i][j]=temp.mat[i][j]/d.mat[j][j];
            }
            d.mat[i][i]=x.mat[i][i];
            for(k=0;k<i;k++)
            {
                d.mat[i][i]-=temp.mat[i][k]*l.mat[i][k];
            }
        }
        for(i=0;i<x.col;i++)
        {
            for(j=0;j<x.row;j++)
            {
                cout<<l.mat[i][j]<<"  ";
            }
            cout<<endl;
        }
        for(i=0;i<x.col;i++)
        {
            for(j=0;j<x.row;j++)
            {
                cout<<d.mat[i][j]<<"  ";
            }
            cout<<endl;
        }
    }
};
