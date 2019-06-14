# -*- coding: utf-8 -*-
"""
Created on Tue May 28 15:35:55 2019

@author: hasee
"""

import numpy as np
import math
def init():
    N=int(input("请输入方程组个数N："))
    A=np.zeros(shape=(N,N))
    B=np.zeros(shape=(N,1))
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
    X=np.zeros(shape=(1,N))
    Y=np.zeros(shape=(1,N))
    print("请输入最大迭代次数")
    M=int(input())
    return A,B,E,N,M,X,Y
def create_BDG(A,B,E,N,M,X,Y):
    for i in range(0,N):
        if abs(A[i][i])<E :
            print("error")
            exit(0)
        T=A[i][i]
        for j in range(0,N):
            if i==j:
                continue
            else:
                A[i][j]/=-T
        B[i][0]/=T
def diedai_jacobi(A,B,X,Y,N,E,K,M):
    for i in range(0,N):
        X[0][i]=B[i][0]
        for j in range(0,N):
            if i==j :
                continue
            else:
                X[0][i]+=A[i][j]*Y[0][j]
    delta=0
    for i in range(0,N):
        delta+=(X[0][i]-Y[0][i])*(X[0][i]-Y[0][i])
    delta=math.sqrt(delta)
    if delta<E:
        print("jacobi迭代结果为:")
        print(X,K)
    else:
        if K<M:
            K+=1
            for i in range(0,N):
                Y[0][i]=X[0][i]
            diedai_jacobi(A,B,X,Y,N,E,K,M)
        else:
            print("max error")
            exit(0)
def diedai_seidel(A,B,X,Y,N,E,K,M):
    for i in range(0,N):
        X[0][i]=B[i][0]
        for j in range(0,N):
            if i==j :
                continue
            else:
                X[0][i]+=A[i][j]*X[0][j]
    delta=0
    for i in range(0,N):
        delta+=(X[0][i]-Y[0][i])*(X[0][i]-Y[0][i])
    delta=math.sqrt(delta)
    if delta<E:
        print("seidel迭代结果为:")
        print(X,K)
    else:
        if K<M:
            K+=1
            for i in range(0,N):
                Y[0][i]=X[0][i]
            diedai_seidel(A,B,X,Y,N,E,K,M)
        else:
            print("max error")
            exit(0)
def jacobi():
    A,B,E,N,M,X,Y=init()
    create_BDG(A,B,E,N,M,X,Y)
    K=1
    diedai_jacobi(A,B,X,Y,N,E,K,M)
def seidel():
    A,B,E,N,M,X,Y=init()
    create_BDG(A,B,E,N,M,X,Y)
    K=1
    diedai_seidel(A,B,X,Y,N,E,K,M)
jacobi()
seidel()