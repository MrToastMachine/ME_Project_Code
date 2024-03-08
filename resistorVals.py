voltage = 5
desired_output = 0.7

res_vals = [
    1,
    2.2,
    4.7,
    7.5,
    10,
    15,
    22,
    33,
    39,
    47,
    56,
    68,
    100,
    120,
    150,
    220,
    330,
    390,
    470,
    510,
    680,
    1000,
    1500,
    2000,
    2200,
    3000,
    4700,
    5100,
    5600,
    7500,
    8200,
    10000,
    15000,
    22000,
    33000,
    47000,
    56000,
    68000,
    75000,
    100000,
    150000,
    220000,
    330000,
    470000,
    680000,
    1000000,
    2000000,
    4700000,
    5600000]

best_R1 = 1
best_R2 = 1
vout = 100
vout_err = 100

errors = []

for R1 in res_vals:
    for R2 in res_vals:
        vout_new = voltage*(R2)/(R1 + R2)
        new_err = abs(vout_new - desired_output)
        errors.append(new_err)
        if (new_err < vout_err):
            vout_err = new_err
            best_R1 = R1
            best_R2 = R2
            vout = vout_new
    
print("Done")

print(f"Min error: {min(errors)}")

print(f"Vout Error: {vout_err}")
print(f"R1 : {best_R1}")
print(f"R2 : {best_R2}")

vout = voltage*(R2)/(R1+R2)
print(f"Output voltage: {vout}")