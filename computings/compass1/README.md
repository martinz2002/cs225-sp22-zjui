# A Not-So-Smart Medical Treatment System

**Author:** Group D1

**Document writer:** Zhong Tiantian

## Project Description

This project aims to realize a medical treatment system under pandemic era, where it records citizen's registration, inoculation and treatment. It allows the following operations:

- **Registration.** The system records a patient's personal information including their ID numbers, names, contact details, professions, dates of birth, and medical risk status. Each registration operation will have a timestamp.
- **Queueing and assignment of appointments.** 
- **Appointment processing.**
- **Reporting.** It produces weekly and monthly reports for users to check.



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

Execute `runsys.exe` or `runsys` to start the system. Normally, it will quite in quite a short while.

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

### Input files format

The following contents describe the format of each input files stored in `../data`.

#### `data/modify_profiles.entries`

This file describes the profile modification operations. It contains several entries, and each entry has several items in the following order:

- **Date:** The date when modification happens.
- **Operation code:** 0 = changing risks, 1 = changing professions
- **ID:** Profile identity
- **The new risk/profession value**

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

Execute `test.exe` or `test` to start the system. Normally, it will quite in quite a short while.

#### Interacting with the System

We made a CLI to allow you use it as you want.

## Some pre-assumptions about the profession/risks, and priority

We assume that lower profession / risk number have higher priority, which indicates that they will be earlier treated and be printed before the larger number of profession/risk.