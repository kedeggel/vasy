## 1.2 Communication via XCTU Console

 + Channel(`CH`): Channel of the WiFi band to use
 + PAN(`ID`): Personal Area Network. Set to 0xFFFF to send to all PANs.
 + Destination Address(`DH`, `DL`): Address inside the PAN set to 0xFFFF to broadcast for the PAN.
 + Source Address(`SH`, `SL`, `MY`: Either 64bit serial number or `MY` for packets with 16 bit address

Setting | COM3      | COM5
--------+-----------+-----
`CH`    | C         | C
`ID`    | 0x4001    | 0x4001
`DH`    | 0x0       | 0x0
`DL`    | 0xFFAA    | 0xFFAA
`MY`    | 0xFFAA    | FFAA
`AP`    | 0x0       | 0x0
`SH`    | 0x13A200  | 0x13A200
`SL`    | 0x40D8AF10| 0x40E4937A

## 1.3 First Configuration of your Module

1. By using the destination address 0xFFFF the packets are broadcasted to the
   PAN meaning that we have to make sure that our **Channel** and **PAN**
   configuration are unique for all groups

2. To set `DL` to 0xFFFF following commands are send:

```
-> +++(no return 0x0D)
<- OK
-> ATDLFFFF
<- OK
-> ATWR
<- OK
-> ATAC
-> ATCN
<- OK
```

## 1.4 A First Range Test

Used 2 XBee Modules without an antenne

After 5 meters just a few packets drop.
Um die Ecke all.


## 1.5 Serial Communication via Arduino
