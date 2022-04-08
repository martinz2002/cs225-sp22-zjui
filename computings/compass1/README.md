# The Not-So-Smart Medical Treatment System (SMTS)

Copyright (C) 2022 Zhejiang University

| Author of the System                              | Document Writer |
| ------------------------------------------------- | --------------- |
| Li Rong, Jiang Wenhan, Zhong Tiantian, Zhou Ruidi | Zhong Tiantian  |

Welcome to the SMTS!

**We strongly recommend you read this document carefully before you get started with the system.**

## Project Description

This project aims to realize a medical treatment system under pandemic era, where it records citizen's registration, inoculation and treatment. It allows the following operations:

- **Registration.** The system records a patient's personal information including their ID numbers, names, contact details, professions, dates of birth, and medical risk status. Each registration operation will have a timestamp.
- **Queueing and assignment of appointments.** 
- **Appointment processing.**
- **Reporting.** It produces weekly and monthly reports for users to check.

## Some pre-assumptions about the profession/risks, and priority

1. We assume that lower profession / risk number have higher priority, which indicates that they will be earlier treated and be printed before the larger number of profession/risk.
2. We assume that people always find the closest available registration points.

## How to use the system?

There are two ways to compile this project:

### Auto-run version

This project allows you to run the system with pre-generated sets of data, including patients' profiles, registration & inoculation point locations, and withdrawals / cancelling operations.

#### Compiling

To compile the auto-run version, run under MacOS/Linux,

````bash
make auto
````

or under Windows,

```shell
mingw32-make auto
```

#### Running the System

Execute `auto.exe` or `auto` to start the system. Normally, it will quite in quite a short while.

#### Getting the Result

The program will write the result in `result.txt`. It should look like this:

```
Welcome to the Silly Medical Treatment System (SMTS). Current date: 2022-4-7 

********************
 Today is 2022-4-8 
********************


...


********************
 Today is 2022-4-13 
********************

plz choose the type of ordering scheme:
0. order of name
 1. order of agegroup
2. order of profession
The following is the weekly report

Queue Waiting: 

Name:a
Age group:3
Profession:3
Risk:1
Waiting time until now:5

Assigned Waiting: 

Treatment: 

********************
 Today is 2022-4-14 
********************


...


********************
 Today is 2022-4-20 
********************

plz choose the type of ordering scheme:
0. order of name
 1. order of agegroup
2. order of profession
The following is the weekly report

Queue Waiting: 

Name:a
Age group:3
Profession:3
Risk:1
Waiting time until now:12

Assigned Waiting: 

Treatment: 

********************
 Today is 2022-4-21 
********************


********************
 Today is 2022-4-22 
********************

...
```

#### Weekly / Monthly reports

The weekly and monthly reports are printed to the console/result file `result.txt`, and

- Before printing, it will ask you through the console terminal the standard for sorting:

  ```
  plz choose the type of ordering scheme:
  0. order of name
   1. order of agegroup
  2. order of profession
  ```

- Then it tells whether this is a monthly report or weekly report:

  ````
  plz choose the type of ordering scheme:
  0. order of name
   1. order of agegroup
  2. order of profession
  The following is the weekly report
  
  Queue Waiting: 
  
  Name:a
  Age group:3
  Profession:3
  Risk:1
  Waiting time until now:12
  
  Assigned Waiting: 
  
  Treatment: 
  ````

#### Input files format

The following contents describe the format of each input files stored in `../data`.

==**<font color="#ff0000">NOTE 1: All `.entries` files should be ended with a string `EOF`, or the program may not work properly.</font>**==

==**<font color="#ff0000">NOTE 2: All operations in `.entries` files should be listed in an order from earlier date to later, if it contains date information.</font>** This simulates the reality that operations are always performed obeying the order of time. The date of the happening of an operation is often the beginning date of that entry.==

##### Profile Modification Information: `data/modify_profiles.entries`

This file describes the profile modification operations. It contains several entries, and each entry has several items in the following order:

- **Date:** The date when modification happens.
- **Operation code:** 0 = changing risks, 1 = changing professions
- **ID:** Profile identity
- **The new risk/profession value**

##### Inoculation Points Information: `data/ino_pts.loc`

This file describes the locations of each inoculation points. It contains several entries, each of them are founded with the following components:

- **`x:`** The $x$ coordinate for the inoculation point.
- **`y:`** The $y$ coordinate for the inoculation point.
- **Capacity:** The maximum number of people to which the inoculation can provide inoculating service on a single day.

##### Registration Points Information: `data/reg_pts.loc`

This file describes the locations of each registration points. It contains several entries, each of them has the following components:

- **`x:`** The $x$ coordinate for the registration point.
- **`y:`** The $y$ coordinate for the registration point.

##### Profiles Information: `data/profiles.entries`

This file describes the profiles to be added on a certain day. It contains several entries, each of them consists of

- **Date:** The date on which the following profile should be added.
- **Name:** Name of the patient.
- **Address**
- **Phone Number**
- **WeChat ID**
- **Email Address**
- **Date of Birth:** Birthday of the patient. Note that the date must be earlier than the current date of the medical system.
- **Risk Level:** Integers 0, 1, 2 or 3, indicating from lowest risk level to highest risk level.
- **Profession Code:** A one-digit number indicating the type of the patient's profession, ranging from 0 to 8.
- **Profile ID:** The ID of the profile. It must be a `int64` number.
- **Registration Point ID:** The ID of the registration point where the patient get registered.

The file is ended with a string `EOF`.

##### Priority Letters: `data/priority_letters.entries`

This file describes the priority letter information. It contains several entries, each of them consists of

- **Date:** The date on which the priority letter is submitted to the system.
- **ID:** The ID of the profile, whose owner has the letter.

This file is ended with a string `EOF`.

##### Withdrawals / Cancellations: `data/withdraw.entries`

This file describes the withdrawals / cancelling withdrawals information. It contains several entries, each of them consists of

- **Date:** The date on which a patient claims a withdrawal / cancellation of previous withdrawal.
- **Operation Code:** 0 = cancel previous withdrawal; 1 = perform a withdrawal
- **ID:** The ID of the profile whose owner claims a withdrawal / cancellation.

### Manual-run version

#### Compiling

To compile the auto-run version, run under MacOS/Linux,

````bash
make manual
````

or under Windows,

```shell
mingw32-make manual
```

#### Running the System

Execute `manual.exe` or `manual` to start the system. Normally, it will quite in quite a short while.

#### Interacting with the System

We made a CLI to allow you use it as you want.

