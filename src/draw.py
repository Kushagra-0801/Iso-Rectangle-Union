import matplotlib 
import matplotlib.pyplot as plt 


f = open('points.txt', 'r').readlines()
rectangle_set = []


# get points from points.txt file

for x in f:

	x = x.split("\n")[0]
	x = x.split(" : ")

	upper_left, lower_right = x[0].split(" "), x[1].split(" ")
	rect = []

	upper_left[0] = int(upper_left[0])
	upper_left[1] = int(upper_left[1])
	rect.append(upper_left)

	lower_right[0] = int(lower_right[0])
	lower_right[1] = int(lower_right[1])
	rect.append(lower_right)

	rectangle_set.append(rect)


# get min and max values of x and y coordinates

mnx, mny = rectangle_set[0][0]
mxx, mxy = rectangle_set[0][0]

for p in rectangle_set:
	
	mnx = min(mnx, p[0][0])
	mnx = min(mnx, p[1][0])

	mny = min(mny, p[0][1])
	mny = min(mny, p[1][1])

	mxx = max(mxx, p[0][0])
	mxx = max(mxx, p[1][0])

	mxy = max(mxy, p[0][1])
	mxy = max(mxy, p[1][1])


# plot the given points

fig = plt.figure() 
ax = fig.add_subplot(111) 

for rect in rectangle_set:

	width =  abs(rect[0][0] - rect[1][0])
	height = abs(rect[0][1] - rect[1][1])
	llp = (rect[0][0], rect[1][1])


	rr = matplotlib.patches.Rectangle(llp, width, height, fc ='none', ec ='g', lw = 1)
	ax.add_patch(rr)


# get the min-max coordinates to set screen limit
plt.xlim([mnx-10, mxx+10]) 
plt.ylim([mny-10, mxy+10]) 


print("Displaying countour, press 'q' to exit")

plt.show() 