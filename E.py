import math


angle=float(input("Angle[degree]: "))
E0=float(input("Initial Energy[MeV]: "))
cos=math.cos(math.radians(angle))
A=float(input("Mass Number: "))


def f(x):
	return (((cos+((cos*cos+x*x-1)**0.5))/(x+1))**2)*E0 


def g(x):
	return (4*x*(cos**2)/((1+x)**2))*E0


print("When this is a proton, its E=" + "{:.4f}".format(f(A))+"[MeV]")
print("When this is a recoil particle, its E=" + "{:.4f}".format(g(A))+"[MeV]")
