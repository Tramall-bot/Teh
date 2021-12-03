def fun(n):
    print("test")
    if n>1:
        return fun(n-1)+fun(n-2)
    else:
        return n
