#!/usr/bin/env python3

############################
##### #!/usr/bin/python3

import sys

end = None

##########################################

def readDane(fname="dane1.txt|"):
  try:
    f=open(fname)
    s = f.readline()
    (W,K) = s.split()    
    W = int(W)
    K = int(K)
    N = int(f.readline())
    # print("wymiary",W,K,N)
    t={}
    t["W"]=W
    t["K"]=K
    t["N"]=N
    
    for w in range(W):
      for k in range(K): t[w,k]=' '
    end
    
    for w in range(W):
      s=f.readline()
      for k in range(K):
        t[w,k]=s[k]
      end
    end
    f.close()
    return t
  except:
    err(1)
  end
end

##########################################

def readRozw(fname="rozw1.txt"):
  try:
    f=open(fname)
    s = f.readline().strip()
    # print("rozwiązanie",s,"\n")
    f.close()
    if s=="BRAK" : err(6)
    return s
  except:
    err(2)
  end
end

##########################################

def err(n):
  error = { 1:"bledny format pliku danych",
            2:"bledny format pliku rozwiazania",
            3:"za dlugie rozwiazanie",
            4:"wpadles na mine",
            5:"za malo diamentow",
            6:"brak rozwiazania",
            7:"bledny kierunek" }
  print("WRONG")
  print("Error",n,":",error[n])
  sys.exit(0)
end

##########################################

def wypisz(t):
  for w in range(t['W']):
    for k in range(t['K']):
      print(t[w,k],end="")
    end
    print()
  end
  print()
end

##########################################

def spr(d,r):
  dx = [0,1,1,1,0,-1,-1,-1]
  dy = [-1,-1,0,1,1,1,0,-1]

  # kontrola długości rozwiazania
  if len(r)>d['N']: err(3)
  
  # liczba diamentów do zebrania
  iled = 0
  for w in range(d['W']):
    for k in range(d['K']):
      if d[w,k]=='+': iled+=1
    end
  end  
  # print("diamentów do zebrania:",iled)

  # pozycja startowa
  for w in range(d['W']):
    for k in range(d['K']):
      if d[w,k]=='.':
        x = k
        y = w
        break
      end
    end
  end
  # print("pozycja startowa",x,y)
  
  
  ld = 0 # licznik diamentów
  for rc in r:
    if not rc in "01234567": err(7)
    kier = int(rc)
    # print("kierunek:",kier)
    while True:
      # print("pozycja:",x,y)
      nx = x+dx[kier]
      ny = y+dy[kier]
      if d[ny,nx]=="+" : 
        ld+=1
        d[ny,nx]=" "
      end
      if d[ny,nx]=="#" : break
      if d[ny,nx]=="*" : err(4)
      x=nx
      y=ny
      if d[y,x]=="O" : break
    end
  end
  # print("zebranych diamentów:",ld)  
  if ld<iled: err(5)
  print("OK")
  sys.exit(0) # sukces
end  

##########################################

if len(sys.argv)<3:
  print("Usage: ./judge.py <file.in> <file.out>")
else:
  finame=sys.argv[1]
  dane=readDane(finame)
  foname=sys.argv[2]
  rozw=readRozw(foname)
  # wypisz(dane)
  spr(dane,rozw)
end

##########################################
