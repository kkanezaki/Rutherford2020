e=1.602*pow(10,-19) 
mp=1.67*pow(10,-27) #proton mass[kg]

E=float(input("proton enrgy[MeV] "))

v=pow((E*2*e*pow(10,6)/mp),0.5)

print("proton velocity Vp = "+"{:.5g}".format(v)+"[m/s]")

t=0.067/v

print("time = "+"{:.5g}".format(t)+"[s]")

