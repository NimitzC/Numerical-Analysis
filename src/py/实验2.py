# -*- coding: utf-8 -*-
"""
Created on Fri Apr 19 14:38:29 2019

@author: hasee
"""

import numpy as np
from matplotlib.pyplot import *
from pylab import *
import math
def f(x):
    return sqrt(x)
def trapezoid(a,b,eps):
    h=(b-a)/2
    n=1
    t1=h*(f(a)+f(b))
    flag=0
    while flag==0:
        t0=t1
        s=0
        for k in range(1,n+1):
            s=s+f(a+(2*k-1)*h/n)
        t1=t0/2+s*h/n
        if abs(t1-t0)<3*eps:
            flag=1
        n=2*n
    print("复化梯形应该分为:",n,"积分值为:",t1)
def simpson(a,b,eps):
    h=(b-a)/2
    n=2
    t0=f(a)+f(b)
    t1=0
    t2=f((a+b)/2)
    s1=h/3*(t0+2*t1+4*t2)
    flag=0
    while flag==0:
        s0=s1
        t1=t1+t2
        t2=0
        for k in range(1,n+1):
            t2=t2+f(a+(2*k-1)*h/n)
        s1=h/(3*n)*(t0+2*t1+4*t2)
        if abs(s1-s0)<15*eps:
            flag=1
        n=2*n
    print("复化抛物线应该分为:",n,"积分值为:",s1)
def romberg(a,b,eps):
    l = [([0] * 100) for i in range(100)]
    l[0][0]=(b-a)/2*(f(a)+f(b))
    for i in range (1,100):
        l[i][0]=l[i-1][0]/2
        for k in range(1,pow(2,i-1)+1):
            mm=pow(2,i)
            l[i][0]=l[i][0]+f(a+(2*k-1)*(b-a)/mm)*(b-a)/mm
        for j in range(1,i+1):
            l[i][j]=(pow(4,j)*l[i][j-1]-l[i-1][j-1])/(pow(4,j)-1)
        if(abs(l[i][i]-l[i-1][i-1])<eps):
            print("romberg应该分为",pow(2,i),"积分值为",l[i][i])
            return
a=input()
b=input()
eps=input()
print("积分上下限为:",a,b,"误差为:",eps)
a=float(a)
b=float(b)
eps=float(eps)
trapezoid(a,b,eps)
simpson(a,b,eps)
romberg(a,b,eps)