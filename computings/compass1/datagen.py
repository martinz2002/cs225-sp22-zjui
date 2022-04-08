import numpy as np
import datetime as dt
import time

today = dt.date.today()

num_of_ino=10;
num_of_reg=10;
num_of_personal_profile=100;
num_of_withdraw_op=10;
num_of_change_op=20;


#generate random date from start date to 10 days later
def gen_date(start_date):
    end_date = start_date + dt.timedelta(days=10)
    return time.strftime("%Y-%m-%d", time.localtime(np.random.randint(time.mktime(start_date.timetuple()), time.mktime(end_date.timetuple()))))

# date_string=gen_date().strftime("%Y-%m-%d")
mytime=gen_date()
print(mytime)
today.strftime(fmt="%Y-%m-%d")



open("data/ino_pts.loc", 'w')

