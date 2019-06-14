# -*- coding: utf-8 -*-
"""
Created on Fri May 24 19:19:56 2019

@author: hasee
"""
import numpy as np
def input_abe():
    N=int(input("请输入方程组个数N："))
    A=np.ones(shape=(N,N))
    B=np.ones(shape=(N,1))
    print("请按行输入系数矩阵A:")
    for i in range(0,N):
        a=input().split(' ')
        for j in range(0,N):
            A[i][j]=float(a[j])
    print("请输入常数项B")
    b=input().split(' ')
    for j in range(0,N):
        B[j][0]=float(b[j])
    print("请输入误差E")
    E=float(input())
    X=np.ones(shape=(1,N))
    return A,B,E,N,X
def xuanzhuyuan(A,B,E,i,N):
    max,index=abs(A[i][i]),i
    for j in range(i+1,N):
        if abs(A[j][i])>max:
            max=abs(A[j][i])
            index=j
    if max<E:
        print("error")
        exit()
    for jj in range(i,N):
        temp=A[i][jj]
        A[i][jj]=A[index][jj]
        A[index][jj]=temp
    temp=B[i][0]
    B[i][0]=B[index][0]
    B[index][0]=temp  
def xiaoqu(A,B,E,N):
    for i in range(0,N-1):
        xuanzhuyuan(A,B,E,i,N)
        for k in range(i+1,N):
            alpha=-A[k][i]/A[i][i] 
            A[k][i]=0
            for j in range(i+1,N):
                A[k][j]+=alpha*A[i][j]
            B[k][0]+=alpha*B[i][0]
def huidai(A,B,N,X):
    for i in range(N-1,-1,-1):
        for j in range(i+1,N):
            B[i][0]-=X[0][j]*A[i][j]
        X[0][i]=B[i][0]/A[i][i]
def lu_fenjie(A,B,L,U,N,E):
    for i in range(0,N):
        max,index=0,0
        for k in range(i,N):
            s=A[k][i]
            for m in range(0,i):
                s-=L[k][m]*U[m][i]
            if abs(s)>max:
                max=abs(s)
                index=k
        if max<E :
            print("error")
            exit()
        for jj in range(0,N):
            temp=A[i][jj]
            A[i][jj]=A[index][jj]
            A[index][jj]=temp
        temp=B[i][0]
        B[i][0]=B[index][0]
        B[index][0]=temp  
        for j in range(i,N):
            U[i][j]=A[i][j]
            for m in range(0,i):
                U[i][j]-=L[i][m]*U[m][j]
        for k in range(i+1,N):
            L[k][i]=A[k][i]/U[i][i]
            for m in range(0,i):
                L[k][i]-=L[k][m]*U[m][i]/U[i][i]
def create_ylu(N):
    Y=np.ones(shape=(N,1))
    L=np.ones(shape=(N,N))
    U=np.ones(shape=(N,N))
    return Y,L,U
def qiulyb(L,B,Y,N):
    for i in range(0,N):
        for j in range(0,i):
            B[i][0]-=Y[j][0]*L[i][j]
        Y[i][0]=B[i][0]
def liezhuyuangaosixiaoqufa():
    A,B,E,N,X=input_abe()
    xiaoqu(A,B,E,N)
    huidai(A,B,N,X)
    print(X)
def liezhuyuanlufenjiefa():
    A,B,E,N,X=input_abe()
    Y,L,U=create_ylu(N)
    lu_fenjie(A,B,L,U,N,E)
    qiulyb(L,B,Y,N)
    huidai(U,Y,N,X)
    print(X)
liezhuyuangaosixiaoqufa()
liezhuyuanlufenjiefa()