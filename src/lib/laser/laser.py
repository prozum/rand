rand = open('/dev/ttyACM0', 'rw')

laser_dist = 1500

velx = 0
vely = 0
velz = 0

if __name__ == '__main__':

    while True:
        rand.write(str(laser_dist))

    while rand.read() != 'armed':
        0

    while True:
        i = rand.read()
        print(i)
        if i.find('yaw') != -1:
            res = int(i[3:])
            if res == 0:
                velz = 0
            elif res == 1250:
                velz = -1
            elif res == 1750:
                velz = 1
            laser_dist -= (velz*10)
            rand.write(str(velz))
        elif i.find('roll') != -1:
            res = int(i[4:])
            if res == 0:
                vely = 0
            elif res == 1250:
                vely = -1
            elif res == 1750:
                vely = 1
            laser_dist -= (velz*10)
            rand.write(str(velz))
        elif i.find('pitch') != -1:
            res = int(i[5:])
            if res == 0:
                velx = 0
            elif res == 1250:
                velx = -1
            elif res == 1750:
                velx = 1
            laser_dist -= (velz*10)
            rand.write(str(velz))
        elif i.find('throttle') != -1:
            res = int(i[8:])
            if res == 0:
                velz = 0
            elif res == 1250:
                velz = -1
            elif res == 1750:
                velz = 1
            laser_dist -= (velz*10)
            rand.write(str(velz))