# SMTS Developer's Document (CA2)

Copyright (C) 2022 Zhejiang University

Written by Zhong Tiantian on 05/03/2022



## Database Design

The ==highlighted== field for each relation is the primary key.

### Person

**The list below is to be made into a table to improve clarity.**

A person object includes the following information:

- **Name `name`:** Name of the patient.
- **Address `address`**
- **Phone Number `phone`**
- **WeChat ID `WeChat`**
- **Email Address `email`**
- **Date of Birth `birthday`:** Birthday of the patient. Note that the date must be earlier than the current date of the medical system.
- **Age Group `agegroup`**
- **Risk Level `risk`:** Integers 0, 1, 2 or 3, indicating from lowest risk level to highest risk level.
- **Profession Code `profession`:** A one-digit number indicating the type of the patient's profession, ranging from 0 to 8.
- ==**Profile ID `ID`:**== The ID of the profile. It must be a `int64` number. **This field should NOT be allowed to modify since it serves as a primary key of this relation.**
- **Registration Point ID `regID`:** The ID of the registration point where the patient get registered.
- **Inoculation Point ID `inoID`:** The ID of the inoculation point where the patient get treatment.
- **Vaccination Sequence `vaccination_sequence`**
- [new] **Type of Treatment:** The type of treatment the patient is to receive. Labelled with type 0, 1 and 2. Type 0 treatment has the highest priority (such as an emergency aid request) while 2 has the lowest.
- **Assignment Status `is_assigned`:** Whether the patient has been assigned a date to receive treatment.
- **Treatment Status `is_inoculated`:** The status recording whether the patient has  his treatment.

### Medical_Status

| Field    | Comment                     |
| -------- | --------------------------- |
| ==Date== | Date of the entry.          |
| Status   | Current status of that day. |

The **status** object:

| Member         | Name                     | Comment                                                      |
| -------------- | ------------------------ | ------------------------------------------------------------ |
| Waiting Queue  | `queueing_personal_file` | Recording who is waiting to be assigned.                     |
| Assigned Queue | `assigned_personal_file` | Recording who has been assigned a treatment operation and is waiting for treatment. |



### Registration

This relation records all registration operations.

| Field                 | Comment |
| --------------------- | ------- |
| ==Profile ID==        |         |
| Date of Registration  |         |
| Registration Point ID |         |



### Treatment

This relation records all treatment operations, including a submission of a priority letter (aka. DDL letter). It contains the following fields:

| Field                           | Comment |
| ------------------------------- | ------- |
| ==Profile ID==                  |         |
| Date of Treatment (Inoculation) |         |
| Type of Treatment               |         |
| Inoculating Point ID            |         |



## New Operations

### Reporting (File I/O)

Generating a report to the specified path.

**Usage:** `report(<int> op, <string> path)`

**Parameter:** `op == 0: weekly; 1: monthly`

By design, all reports should be generated to `../reports` folder. The name format is `<type>_<number_of_report>_<mm_dd_yyyy>.report`. For example, report `monthly_5_10_01_2002.report` contains reported data for the fifth month since the system runs, which is generated on October 1st, 2002.
