# Address Map (Human-readable)

## Overview
- Base: `0x0800F400`
- Total entries: `100`
- Entry size: `2 bytes`
- Section stride: `8 bytes` (4 entries)

## Table
| No | Address    | Base+Offset | Section               | Field                   | Note |
|---:|------------|-------------|-----------------------|-------------------------|------|
| 0  | 0x0800F400 | +0x0000 | MACHINE_NAME_1        | chunk1                  | or |
| 1  | 0x0800F402 | +0x0002 | MACHINE_NAME_1        | chunk2                  | bi |
| 2  | 0x0800F404 | +0x0004 | MACHINE_NAME_1        | chunk3                  | ta |
| 3  | 0x0800F406 | +0x0006 | MACHINE_NAME_1        | chunk4                  | lx |
| 4  | 0x0800F408 | +0x0008 | MACHINE_NAME_2        | reserve1                | - |
| 5  | 0x0800F40A | +0x000A | MACHINE_NAME_2        | reserve2                | - |
| 6  | 0x0800F40C | +0x000C | MACHINE_NAME_2        | reserve3                | - |
| 7  | 0x0800F40E | +0x000E | MACHINE_NAME_2        | reserve4                | - |
| 8  | 0x0800F410 | +0x0010 | MACHINE_INFO_1        | chunk1                  | 2. |
| 9  | 0x0800F412 | +0x0012 | MACHINE_INFO_1        | chunk2                  | 0. |
| 10 | 0x0800F414 | +0x0014 | MACHINE_INFO_1        | chunk3                  | 1 |
| 11 | 0x0800F416 | +0x0016 | MACHINE_INFO_1        | reserve                 | - |
| 12 | 0x0800F418 | +0x0018 | MACHINE_INFO_2        | reserve1                | - |
| 13 | 0x0800F41A | +0x001A | MACHINE_INFO_2        | reserve2                | - |
| 14 | 0x0800F41C | +0x001C | MACHINE_INFO_2        | reserve3                | - |
| 15 | 0x0800F41E | +0x001E | MACHINE_INFO_2        | reserve4                | - |
| 16 | 0x0800F420 | +0x0020 | PID_VEL_1             | kp_h                    | - |
| 17 | 0x0800F422 | +0x0022 | PID_VEL_1             | kp_l                    | - |
| 18 | 0x0800F424 | +0x0024 | PID_VEL_1             | ki_h                    | - |
| 19 | 0x0800F426 | +0x0026 | PID_VEL_1             | ki_l                    | - |
| 20 | 0x0800F428 | +0x0028 | PID_VEL_2             | kd_h                    | - |
| 21 | 0x0800F42A | +0x002A | PID_VEL_2             | kd_l                    | - |
| 22 | 0x0800F42C | +0x002C | PID_VEL_2             | reserve1                | - |
| 23 | 0x0800F42E | +0x002E | PID_VEL_2             | reserve2                | - |
| 24 | 0x0800F430 | +0x0030 | PID_ANG_VEL_1         | kp_h                    | - |
| 25 | 0x0800F432 | +0x0032 | PID_ANG_VEL_1         | kp_l                    | - |
| 26 | 0x0800F434 | +0x0034 | PID_ANG_VEL_1         | ki_h                    | - |
| 27 | 0x0800F436 | +0x0036 | PID_ANG_VEL_1         | ki_l                    | - |
| 28 | 0x0800F438 | +0x0038 | PID_ANG_VEL_2         | kd_h                    | - |
| 29 | 0x0800F43A | +0x003A | PID_ANG_VEL_2         | kd_l                    | - |
| 30 | 0x0800F43C | +0x003C | PID_ANG_VEL_2         | reserve1                | - |
| 31 | 0x0800F43E | +0x003E | PID_ANG_VEL_2         | reserve2                | - |
| 32 | 0x0800F440 | +0x0040 | WALL_SENSOR_REF_RIGHT | rfront                  | - |
| 33 | 0x0800F442 | +0x0042 | WALL_SENSOR_REF_RIGHT | lfront                  | - |
| 34 | 0x0800F444 | +0x0044 | WALL_SENSOR_REF_RIGHT | rside                   | - |
| 35 | 0x0800F446 | +0x0046 | WALL_SENSOR_REF_RIGHT | lside                   | - |
| 36 | 0x0800F448 | +0x0048 | WALL_SENSOR_REF_LEFT  | rfront                  | - |
| 37 | 0x0800F44A | +0x004A | WALL_SENSOR_REF_LEFT  | lfront                  | - |
| 38 | 0x0800F44C | +0x004C | WALL_SENSOR_REF_LEFT  | rside                   | - |
| 39 | 0x0800F44E | +0x004E | WALL_SENSOR_REF_LEFT  | lside                   | - |
| 40 | 0x0800F450 | +0x0050 |  |  |  |
| 41 | 0x0800F452 | +0x0052 |  |  |  |
| 42 | 0x0800F454 | +0x0054 |  |  |  |
| 43 | 0x0800F456 | +0x0056 |  |  |  |
| 44 | 0x0800F458 | +0x0058 |  |  |  |
| 45 | 0x0800F45A | +0x005A |  |  |  |
| 46 | 0x0800F45C | +0x005C |  |  |  |
| 47 | 0x0800F45E | +0x005E |  |  |  |
| 48 | 0x0800F460 | +0x0060 |  |  |  |
| 49 | 0x0800F462 | +0x0062 |  |  |  |
| 50 | 0x0800F464 | +0x0064 |  |  |  |
| 51 | 0x0800F466 | +0x0066 |  |  |  |
| 52 | 0x0800F468 | +0x0068 |  |  |  |
| 53 | 0x0800F46A | +0x006A |  |  |  |
| 54 | 0x0800F46C | +0x006C |  |  |  |
| 55 | 0x0800F46E | +0x006E |  |  |  |
| 56 | 0x0800F470 | +0x0070 |  |  |  |
| 57 | 0x0800F472 | +0x0072 |  |  |  |
| 58 | 0x0800F474 | +0x0074 |  |  |  |
| 59 | 0x0800F476 | +0x0076 |  |  |  |
| 60 | 0x0800F478 | +0x0078 |  |  |  |
| 61 | 0x0800F47A | +0x007A |  |  |  |
| 62 | 0x0800F47C | +0x007C |  |  |  |
| 63 | 0x0800F47E | +0x007E |  |  |  |
| 64 | 0x0800F480 | +0x0080 |  |  |  |
| 65 | 0x0800F482 | +0x0082 |  |  |  |
| 66 | 0x0800F484 | +0x0084 |  |  |  |
| 67 | 0x0800F486 | +0x0086 |  |  |  |
| 68 | 0x0800F488 | +0x0088 |  |  |  |
| 69 | 0x0800F48A | +0x008A |  |  |  |
| 70 | 0x0800F48C | +0x008C |  |  |  |
| 71 | 0x0800F48E | +0x008E |  |  |  |
| 72 | 0x0800F490 | +0x0090 |  |  |  |
| 73 | 0x0800F492 | +0x0092 |  |  |  |
| 74 | 0x0800F494 | +0x0094 |  |  |  |
| 75 | 0x0800F496 | +0x0096 |  |  |  |
| 76 | 0x0800F498 | +0x0098 |  |  |  |
| 77 | 0x0800F49A | +0x009A |  |  |  |
| 78 | 0x0800F49C | +0x009C |  |  |  |
| 79 | 0x0800F49E | +0x009E |  |  |  |
| 80 | 0x0800F4A0 | +0x00A0 |  |  |  |
| 81 | 0x0800F4A2 | +0x00A2 |  |  |  |
| 82 | 0x0800F4A4 | +0x00A4 |  |  |  |
| 83 | 0x0800F4A6 | +0x00A6 |  |  |  |
| 84 | 0x0800F4A8 | +0x00A8 |  |  |  |
| 85 | 0x0800F4AA | +0x00AA |  |  |  |
| 86 | 0x0800F4AC | +0x00AC |  |  |  |
| 87 | 0x0800F4AE | +0x00AE |  |  |  |
| 88 | 0x0800F4B0 | +0x00B0 |  |  |  |
| 89 | 0x0800F4B2 | +0x00B2 |  |  |  |
| 90 | 0x0800F4B4 | +0x00B4 |  |  |  |
| 91 | 0x0800F4B6 | +0x00B6 |  |  |  |
| 92 | 0x0800F4B8 | +0x00B8 |  |  |  |
| 93 | 0x0800F4BA | +0x00BA |  |  |  |
| 94 | 0x0800F4BC | +0x00BC |  |  |  |
| 95 | 0x0800F4BE | +0x00BE |  |  |  |
| 96 | 0x0800F4C0 | +0x00C0 |  |  |  |
| 97 | 0x0800F4C2 | +0x00C2 |  |  |  |
| 98 | 0x0800F4C4 | +0x00C4 |  |  |  |
| 99 | 0x0800F4C6 | +0x00C6 |  |  |  |
