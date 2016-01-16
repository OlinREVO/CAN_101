# CAN From AVR Freaks tutorial
I did not write this, it is a copy/paste from an tutorial that can be found [here (LINK)](http://www.avrfreaks.net/forum/tut-using-8-bit-avr-controller-area-network-can-register). The formatting of the original article was just atrocious, so I put it here.

### Using the basic 8 bit AVR CAN registers:

The CAN controller hardware is a built-in state machine that handles low level CAN protocol operations. Its interface to control/use this hardware is through the AVR Special Function I/O Registers (`SFIORs`).

First there are CAN General registers (see the data sheet chapter). These registers have reset default bit values. When the AVR is reset or when the CAN General register `CANGCON.SWRES` bit is set and the CAN hardware is reset, the General registers have their bits set to the default values from the AVR data sheet. For example look at an 8 bit AVR CAN data sheet description for CAN General Control Register `CANGCON`. Under the figure showing all the bit names there is an Initial Value row. The Initial Value row shows you what the reset default bit values are.

Second there are CAN Mob registers (see the data sheet chapter). These registers have no reset default values and have garbage values in them after a reset. The Mob registers are actually duplicate register groups that are accessed using the General register `CANPAGE` as a pointer to one specific register group. Look in the data sheet at CAN Page MOb Register - `CANPAGE`. The `CANPAGE` `MOBNB3`, `MOBNB2`, `MOBNB1` and `MOBNB0` bits address which Mob register group your code may access. For example in the `AT90CANxxx` family there are 15 Mob register groups. Setting the `CANPAGE MOBNBn` bits points to the specific Mob register group number n, only one specific number n of the 15 register groups that your code may access. Think of each different Mob number n register group as assigning a single task to the CAN state machine hardware.

The `CANCDMOB` register `CONMOB1` and `CONMOB0` bits determine the CAN task being assigned to each MOb and writing `CANCDMOB` also starts the CAN task. So, writing `CANCDMOB` is always done last after all the other registers have already been setup. Since writing to any bit in `CANCDMOB` will always also write to the `CONMOBn` bits, writing `CANCDMOB` is only done one time for each MOb task. When a `Tx` or `Rx` CAN MOb task is started, the read only `CANEN` register `ENMOBn` bit corresponding to the MOb number n is automatically set and the MOb is busy. After the CAN hardware finishes with the MOb task, then it automatically clears this `CANEN` register `ENMOBn` bit. Writing the `CONMOBn bits =0` disable is also a valid CAN MOb task (except the `MOb CANEN` bit is not automatically set). Like all CAN MOb tasks, the disable task is only a request sent to the CAN hardware and your code must detect when the actual MOb disable task completes by checking its `CANEN` bit.

In the data sheet, the Read/Write row R/W means the bit value may be Read or Written by your code and a R means your code may only Read this bit value. This is very important to pay attention to if you ever want to understand how the CAN hardware interface operates. If you ever think you want to write any value to any CAN register bit, but that bit is Read only, your understanding of how to use the CAN hardware is wrong!

Each Mob register group includes 8 `CANMSG` bytes. Each Mob number n register group addresses each individual CANMSG byte using the `CANPAGE` `INDX2`, `INDX1` and `INDX0` pointer bits. These `INDXn` bits always determine which `CANMSG` byte your code accesses when `CANMSG` is read or written. The `CANPAGE.AINC` bit may be cleared to automatically increment the `CANPAGE.INDXn` bits after `CANMSG` is read or written by your code.

For example; `CANPAGE = 0x32` points at MOb register group 3, `CANMSG` byte 2 with automatic increment of the `CANPAGE` `INDXn` bit value after any read or write of the `CANMSG` register. In the `AT90CANXXX` family the fifteen MOb group `CANMSG` `MOBNBn` values are zero to fourteen and the `CANMSG` `INDXn` index values are zero to seven. The `CANPAGE.AINC=0` automatic `CANPAGE.INDXn` increment overflows the `INDXn` value from seven back to zero.

After a CAN reset when your code initializes the CAN registers, every `MOb CANPAGE` register group (even if your code never uses the MOb register group), must set its `CANCDMOB` and `CANSTMOB` registers to zero before `CANGCON.ENASTB` is set to enable the CAN hardware. This disables each MOb and clears all the MOb register interrupt/polling flags. All the other MOb registers do not have to be set to any value until later when you actually assign a task to the MOb. The CAN reset initializes all the General register bits.

The data sheet chapter on CAN interrupts figure shows which registers configure the interrupt or polling CAN MOb activity detection. Only if `CANGIE.ENIT` is set you must provide the AVR interrupt vector 19 CAN IT interrupt code. If `CANGIE.ENIT` is cleared, your code polls the `CANGIT.CANIT` bit to detect MOb task activity. Notice there are read only registers and read only register bits in this figure. There are also other R/W CANGIT General register activity flags in addition to the CANSTMOB MOb register activity flags.

The read only CANSIT register bits work with the CANHPMOB register to use the CAN hardware to find which MObs have any activity in their CANSTMOB register. The CANSIT bits are only set for the corresponding CANSTMOB bits enabled with CANGIE.ENTX, CANGIE.ENRX or CANGIE.ENERR bits. See the data sheet CANHPMOB explanation. This CANHPMOB register support allows your code to rapidly find out which MObs need to have active CANSTMOB flags serviced and ignore MObs with no CANSTMOB activity.

When the CAN hardware sets any CANSTMOB register bit in any MOb group and that CANSTMOB bit is enabled by CANGIE.ENTX, CANGIE.ENRX or CANGIE.ENERR bits, the read only CANSIT register SITn bit for the MOb is set. The CANSIT register may be read by your software, but its primary purpose is to support CANHPMOB. When your software clears the enabled CANSTMOB bits, the CANSIT bit for the MOb is cleared and CANHPMOB now ignores this serviced MOb. Next any MOb that has any task assigned must have its CANIE register IEMOBn bit for the MOb set. In fact the CANIE bits may be set for any MOb that could ever be used, during CAN initialization and left that way.

After a MOb task completes and a CANSTMOB.RXOK or CANSTMOB.TXOK bit is set by the CAN hardware, the MOb is automatically disabled and its corresponding CANEN register ENMOBn bit is cleared. The CAN hardware sets the MOb CANSTMOB RXOK or TXOK bit and your program code must clear CANSTMOB after responding to this MOb task activity. Unlike RXOK or TXOK, when any CANSTMOB error bits are set by the CAN hardware the MOb CANEN register bit is not automatically disabled, unless the current MOb task is a just completed MOb disable command that ended with a final MOb error. The CANGCON.ABRQ abort all MObs request also takes time to complete and the single possible MOb that might already be busy using the CAN bus could still complete normally and set any of its CANSTMOB flags (MOb disable commands and aborts do not immediately terminate the active on-going communication MOb already using the CAN bus). Clearing CANGCON.ENASTB=0 (disabling the entire CAN module) also has on-going communication issues. Only setting CANGCON.SWRES=1 will immediately terminate all on-going communication and probably cause errors in other CAN nodes by doing this.

When the MOb CANEN bit is already cleared, writing a CANCDMOB command to disable the MOb is immediate with no delay because the MOb is already disabled. Anytime a MOb CANEN bit is already set, writing a CANCDMOB command to disable the MOb is a request that takes time to complete before the CAN hardware clears the MOb CANEN bit. If the busy MOb disable request fails, the MOb may possibly still complete and disable with a CANSTMOB RXOK, TXOK or final error flag.

### CAN Initialization:
```
 Write CANGCON.SWRES=1
    Initialize any CAN code global variables here while the CAN hardware is idle
    For all MOb groups:
        Write CANPAGE=MOb number
        Write CANCDMOB=0
        Write CANSTMOB=0
    Write CANBT1, CANBT2 and CANBT3 with the CAN baud setup values
    Write CANGIE to your desired configuration
        CANGIE.ENIT=0 for polling using the read only CANGIT.CANIT bit
        CANGIE.ENIT=1 for interrupts using AVR interrupt vector 19
        See the data sheet Figure CAN Controller Interrupt Structure for more CANGIE info
    Write CANIE1 and CANIE2 bits, typically =1 for all MObs to be used
    If desired write the CANHPMOB CGP3, CGP2, CGP1 and CGP0 bits
        Typically the General register CANHPMOB reset default is the most useful
    If you are using time stamping write CANTCON with any desired non-zero value
        The General register CANTCON reset default is already zero
    All other CAN General registers are initialized by the SWRES above
    Write CANGCON.ENASTB=1
```

The CANGCON.SWRES=1 resets the CAN hardware, which always recovers from any CAN Rx state machine confusion. Since the General CAN registers are all initialized by this reset, all CAN interrupts and activity are safely disabled until after CANGCON.ENASTB=1 (you do not need to disable AVR global interrupts for CAN initialization when you use SWRES). You do not need to wait for the CAN hardware to set CANGSTA.ENFG, but if you do wait you must provide a wait length time out in case the CAN hardware fails to start. For example, if the physical CAN bus is stuck in a dominant state the CAN hardware will never set ENGF and you do not want to disable the entire AVR chip forever waiting on something that will never happen. After CANGCON.ENASTB=1 the CAN will accept new tasks, but none of these tasks will run or complete until after the CAN hardware sets CANGSTA.ENFG.

### CAN MOb Tx task initialization:

```
Make sure the MOb n CANEN1, CANEN2 ENMOBn bit is cleared (the MOb is not busy)*
        Never use an already busy MOb to Tx
    Write CANPAGE.MOBNBn=MOb number and CANPAGE.INDXn=0
        CANPAGE.AINC=0 is the usual setting
    Make sure the MOb CANSTMOB value is cleared*
        The polling or interrupt code must finish with and clear CANSTMOB for this MOb first
    Write CANIDT1, CANIDT2, CANIDT3 and CANIDT4 to the CAN ID value (see IDE bit below)
        Write all unused/reserved bits=0
    Write CANIDT4.RTRTAG=0 for CAN Data Frame, or =1 for CAN Remote Frame
    Write CANIDM1, CANIDM2, CANIDM3 and CANIDM4 all =0
        None of the CANIDM registers are used by a Tx, but the data sheet said to clear all reserved bits
    Sequentially write all CANMSG bytes to be sent in the Tx (8 bytes maximum)
        If CANPAGE.AINC=0 the CANPAGE.INDXn value will auto-increment after each write
        If CANPAGE.AINC=1 you must change the CANPAGE.INDXn value for each CANMSG write
    Write CANCDMOB.CONMOBn=01 enable transmission
        Also write CANCDMOB.IDE=0 for 11 bit IDs, or =1 for 29 bit IDs
        Also write CANCDMOB.DLCn to match the number of CANMSG bytes written (8 bytes maximum)
        Also always write CANCDMOB.RPLV=0
        All four of these CANCDMOB register bit writes are all done together one time only for each MOb task
```

### CAN MOb normal Rx task initialization:

```
 Make sure the MOb n CANEN1, CANEN2 ENMOBn bit is cleared (the MOb is not busy)*
        Never use an already busy MOb to Rx
    Write CANPAGE.MOBNBn=MOb number and CANPAGE.INDXn=0
        CANPAGE.AINC=0 is the usual setting
    Make sure the MOb CANSTMOB value is cleared*
        The polling or interrupt code must finish with and clear CANSTMOB for this MOb first
    Write CANIDT1, CANIDT2, CANIDT3 and CANIDT4 to the CAN ID value (see IDE bit below)
        Write all unused/reserved bits=0
    Write CANIDT4.RTRTAG=0 for CAN Data Frame, or =1 for CAN Remote Frame
    Write CANIDM1, CANIDM2, CANIDM3 and CANIDM4 IDMSKn bits to:
        =0 for any IDMSKn bit you want to mask (ignore the corresponding CANIDT.IDTn bit value)
        =1 for any IDMSKn bit you want to match (use the corresponding CANIDT.IDTn bit value)
        Write all unused/reserved bits=0
    Write CANIDM4.RTRMSK=1 to match CANIDT4.RTRTAG, or =0 to ignore CANIDT4.RTRTAG
        =0 will Rx either CAN Data Frames or CAN Remote Fames
        =1 will only Rx the CAN frame type set in CANIDT4.RTRTAG
    Write CANIDM4.IDEMSK=1 to match CANCDMOB.IDE, or =0 to ignore CANCDMOB.IDE
        =0 will Rx either 11 bit CAN IDs or 29 bit CAN IDs
        =1 will only Rx the CAN ID length set in CANCDMOB.IDE
    Write CANCDMOB.CONMOBn=10 enable reception for a normal Rx
        If CANIDM4.IDEMSK is zero
            Also write CANCDMOB.IDE=1 (only use 29 bit IDs in this case)
        if CANIDM4.IDEMSK is one
            Also write CANCDMOB.IDE=0 for 11 bit IDs, or =1 for 29 bit IDs
        Also write CANCDMOB.DLCn to match the number of CANMSG bytes expected to Rx (8 bytes maximum)
        Also write CANCDMOB.RPLV=0 for a normal Rx
        All four of these CANCDMOB register bit writes are all done together one time only for each MOb task
```

The CANEN check for MOb busy and CANSTMOB cleared check may be skipped the very first use after the CAN hardware is initialized. If your program never sets a MOb disable task and your program code flow always waits for the CANSTMOB.TXOK or CANSTMOB.RXOK code to finish first, you may skip these two checks. If your program code only uses a CANCDMOB.CONMOBn=0 MOb busy check and does not ever check CANEN1 or CANEN2 for MOb busy, you must never set any MOb disable task, because the write CONMOBn=0 disable command reads as zero (false not busy) when the CANEN MOb bit is still set to busy while a disable request is active (the correct CANEN1 or CANEN2 MOb bit is the only true MOb busy indicator). If you really need to use a busy MOb for a new MOb Tx or Rx task, use a MOb disable task, wait for the CANEN MOb busy bit to clear first, process any MOb activity if any (CANSTMOB) and then use the MOb for the new task.

It is important to preserve the General register CANEN ENMOBn bit check, set MOb n register CANPAGE value and then check CANSTMOB sequence. Since in theory the CANEN bit and CANSTMOB values are changed simultaneously by the CAN hardware, using this sequence ensures they are always detected accurately by your program code.

When CANIDM4.IDEMSK=0 always use CANCDMOB.IDE=1 (29 bit long ID). If CANCDMOB.IDE=0 and CANIDM4.IDEMSK=0 you are setting up an 11 bit ID Rx MOb that might return a 29 bit ID result because IDEMSK=0 (it makes no sense and cripples your Rx MOb setup to use an 11 bit ID setup for a possible 29 bit ID read). A CANCDMOB.IDE=0 with CANIDM4.IDEMSK=0 and all CANIDM IDEMSKn bits =0 with all CANIDT IDTn bits =0 exception is seen in the "CAN transmission after 3-bit intermission" AT90CANxxx family errata. This only works correctly because all 29 CANIDM IDEMSKn bits are =0 (masked).

Anytime any MOb disables and automatically clears its corresponding CANEN register ENMOBn bit (disables), this MOb CANCDMOB register CONMOB1 and CONMOB0 bits are not changed. The last MOb command is still shown in these CANCDMOB bits after the MOb completes. The MOb will not re-enable until your code writes CANCDMOB with another command. If you want to clear these CANCDMOB command bits to zero, your code will have to do it after the MOb disables and clears its CANEN bit (when RXOK or TXOK is handled is a good place to do this clear if you want to do it).

The CANPAGE register INDXn=0 CANMSG byte is always the first one sent or received on the CAN bus. It does not matter what INDXn order your code writes CANMSG bytes in, but the order they are used in by the CAN hardware is fixed starting at CANMSG byte number 0 up to CANMSG byte number 7 depending on the DLCn length value.

### How to process CANSTMOB.TXOK activity set by the CAN hardware:
```
  Write CANPAGE.MOBNBn=MOb number
    Check that CANSTMOB.TXOK is set
        When TXOK is set all CANSTMOB error bits are cleared
    Read CANSTMH and CANSTML if your code uses time stamps
    Write CANSTMOB=0
```

If CANCDMOB.RPLV was set when the Rx MOb Remote Frame task was initialized, the CANSTMOB.TXOK response becomes a composite of a Rx MOb Remote Frame with an automatic reply Tx Data Frame from the same MOb that ends with a TXOK (there is no RXOK and the RPLV bit is cleared before the TXOK). This complicates any RPLV enabled TXOK processing (see the data sheet).

I find it is simpler, cleaner and more flexible to never use CANCDMOB.RPLV=1 and do this function (if you want to use it) in your software instead. Using software allows your Tx reply to use fresh node data and even use a different reply ID if desired. Using RPLV=1 must set up the reply data first thing when the Rx Remote Frame MOb task is initialized, possibly long before this Rx MOb receives the actual request, and the automatic Tx Data Frame reply ID must match the same Rx Remote Frame request ID (no choice).

### How to process CANSTMOB.RXOK activity set by the CAN hardware:

```
 Write CANPAGE.MOBNBn=MOb number and CANPAGE.INDXn=0
        CANPAGE.AINC=0 is the usual setting
    Check that CANSTMOB.RXOK is set
        When RXOK is set all CANSTMOB error bits are cleared
        Only when RXOK is set the DLCW bit might also be set
    Read CANSTMH and CANSTML if your code uses time stamps
    If CANIDM4.IDEMSK is zero
        Read CANCDMOB.IDE to get the new Rx ID length (=0 is 11 bit ID, =1 is 29 bit ID)
        You must know IDE to read the CANIDT1, CANIDT2, CANIDT3 and CANIDT4 ID value
        If the old IDE is changed by the new IDE value you must (also true if IDMSKn bits=0):
            Read the new CANIDT1, CANIDT2, CANIDT3 and CANIDT4 ID value using the new IDE value    
    If CANIDM4.RTRMSK is zero
        Read CANIDT4.RTRTAG to get the new Rx frame type (=0 is Data Frame, =1 is Remote Frame)
    If CANIDM1, CANIDM2, CANIDM3 or CANIDM4 have any IDMSKn bits=0 you must:
        Read the new CANIDT1, CANIDT2, CANIDT3 and CANIDT4 ID value using the IDE value
    If CANCDMOB.IDE is zero, CANIDM4.IDEMSK is zero and you might re-enable this MOb task later:
        Restore the original CANIDT2, CANIDT3 and CANIDT4 bit values numbered 20 through 3 + clear bit 1
    If CANCDMOB.IDE is zero, CANIDM4.IDEMSK is one and you might re-enable this MOb task later:
        Clear the CANIDT2, CANIDT3 and CANIDT4 reserved bits numbered 20 through 3 + bit 1
    Read the new CANCDMOB.DLCn value and limit it to a value of 8 maximum (very important)
    If CANIDT4.RTRTAG is zero (only a CAN Data Frame has any CANMSG bytes)
        Sequentially read the limited DLCn number of CANMSG bytes to get the CAN data
            If CANPAGE.AINC=0 the CANPAGE.INDXn value will auto-increment after each read
            If CANPAGE.AINC=1 you must change the CANPAGE.INDXn value for each CANMSG read
    Write CANSTMOB=0
```

The CANSTMOB TXOK and RXOK bits are never set together at the same time by the CAN hardware. Never forget CANSTMOB is a MOb register, so setting a known General CANPAGE register value is always required first before accessing any specific MOb CANSTMOB value (or before accessing any other MOb register).

When using a MOb n 11 bit ID (CANCDMOB.IDE=0), after the CANSTMOB.RXOK the CANIDT2, CANIDT3 and CANIDT4 reserved bits numbered 20 to 3 plus bit 1 are updated with random values (see the data sheet CAN Identifier Tag Registers - CANIDT1, CANIDT2, CANIDT3, and CANIDT4). If CANIDM4.IDEMSK=1 and you reuse these CANIDT2, CANIDT3 and CANIDT4 register values to re-enable the MOb n Rx task, you must clear all of these updated randomized reserved bits first. If CANIDM4.IDEMSK=0 and you reuse these CANIDT2, CANIDT3 and CANIDT4 register values to re-enable the MOb n Rx task, you must restore all of these updated randomized reserved bits to their original value first. Only if CANCDMOB.IDE=0, CANIDM4.IDEMSK=0 and all CANIDM2, CANIDM3, CANIDM4 bit numbers 20 through 3 are all zero values (masked) then the original value of the CANIDT2, CANIDT3 and CANIDT4 register bits 20 through 3 does not matter (CANIDT4 bit 1 still must be cleared). When re-enabling the Rx MOb n, the other solution is not to use the existing CANIDT2, CANIDT3 and CANIDT4 values and always start over by writing new values if you re-enable this MOb.

Upon CANSTMOB.RXOK the DLCW bit use is optional. When you setup the Rx MOb the CANCDMOB.DLCn value is set to the expected number of CANMSG bytes to Rx. The actual CAN Rx will overwrite the expected DLCn value, and if the actual DLCn value is different from the original now overwritten and lost expected DLCn value, the CANSTMOB.DLCW bit will be set. If you always get the new DLCn value after a RXOK, the CANSTMOB.DLCW bit is only really important when CANCDMOB.RPLV=1 in a CAN Remote Frame Rx MOb.

As shown above, several CAN MOb register values may be updated and changed by a CAN Rx. The CANSTMOB.RXOK response may be simpler. For example, if your program only ever uses CANIDM4.IDEMSK=1 you know the ID length will always be exactly what you set in CANCDMOB.IDE. If you always have CANIDT4.RTRTAG=0 and CANIDM4.RTRMSK=1 is always true, you never need to check for CAN Remote Frames and you will always have DLCn number of CANMSG bytes to read. If none of the CANIDM1, CANIDM2, CANIDM3 or CANIDM4 values have any IDMSKn bits=0 and CANIDM4.IDEMSK=1 the CANIDT1, CANIDT2, CANIDT3 and CANIDT4 ID Rx value will not change, so you may substitute the RXOK MOb number n for this known ID value and not bother reading the CANIDT registers ID value. If you never re-enable an 11 bit ID Rx MOb with old CANIDT values it gets simpler.

The above TXOK and RXOK processing descriptions do not cover if software polling of CANGIT.CANIT or if the hardware CAN IT AVR vector 19 interrupt is used to respond to the MOb activity. Your software must clear CANSTMOB when finished processing the polling or interrupt MOb activity response. If you use the CAN IT interrupt, you must first save the CANPAGE value, then restore this saved CANPAGE value before returning from the interrupt response. If you fail to clear any active MOb CANSTMOB bits while using interrupts, you will get really slowed down in an infinite CAN IT interrupt response loop (one single non-interrupt instruction always executes between repeated interrupt responses).

The CANHPMOB register may be used in a polling or CAN IT interrupt response to quickly locate only the MOb CANSTMOB registers that require attention and ignore any MObs that do not need service.

The General CANGIT flags are cleared by writing a one to the flag bit or flag bits you want to clear. This is how AVR interrupt flags are normally cleared. It is the CANSTMOB flags that are different and are cleared by writing a zero.

What the data sheet said about the CANSTMOB flag bits "It must be cleared using a read-modify-write software routine on the whole CANSTMOB register.", what was actually meant is the must only applies to only clearing a specific bit. It is perfectly acceptable to simply write CANSTMOB=0 when without any read-modify-write cycle when you want to clear the entire CANSTMOB register, but the MOb should already be disabled (except for the busy MOb clear CANSTMOB error flags exception - see below).

Keep in mind the MOb CANSTMOB.TXOK or CANSTMOB.RXOK automatically disables the MOb (the MOb CANEN bit is cleared). When a MOb is disabled it is safe to read or write the MOb registers, up until CANCDMOB is written again. Safe means the CAN hardware will not change any MOb register values or get confused if your program code changes any MOb register values. Anytime the MOb CANEN1 or CANEN2 MOb bit is set and the MOb is busy, it is not safe to read or write any MOb registers (except reading any CANSTMOB is always safe). The only three unsafe write exceptions are when writing a new MOb disable task to a busy MOb, when clearing CANSTMOB error flags when CANGIE.ENRR=1, or when writing CANCDMOB for the "CAN transmission after 3-bit intermission" AT90CANxxx family errata. If CANGIE.ENRR=0 the CANSTMOB error flags will not be responded to, so just ignore the CANSTMOB error flags.

After a MOb CANSTMOB TXOK or RXOK bit is automatically set (the MOb disables), all the information in the MOb registers is safe until you write to any of those MOb registers or start another MOb task by writing to that CANCDMOB. You must extract (read) all MOb information from a completed MOb before you may reuse that MOb for a new task. This means the polling or interrupt code may extract the MOb information immediately then re-enable the MOb, or the MOb information may be extracted later from the still unchanged disabled MOb registers. If you are using interrupts this means you may delay extracting MOb information, as in do it later after the CAN IT interrupt code clears CANSTMOB and returns. Usually in this delayed case a dedicated MOb global software flag value is used to signal the non-interrupt code that it needs to extract MOb information. Either choice of an immediate extraction or a delayed extraction depends on how fast you may need to re-enable a MOb. An immediate extraction usually takes more SRAM to copy MOb information into.

A new 11 bit ID CAN Frame Rx has 19 CAN bit times (bit times depend on the CAN baud) after the RXOK to re-enable the MOb without any possibility of missing any new CAN Frames. A new 29 bit ID CAN Frame Rx has 39 CAN bit times after the RXOK to re-enable. If you need additional time to re-enable a RXOK automatically disabled Rx MOb task, you may create duplicate Rx MOb tasks in multiple Rx MObs. The lowest MOb number n will take the first RXOK, leaving all higher numbered MOb n tasks still enabled and ready for the next Rx without any delay. The extra duplicate MOb or MObs will give you lots of time to extract MOb data and re-enable the disabled MOb or MObs without any loss of any new Rx CAN Frames.

Whenever possible, 8 bit AVR chip global software flags shared in an interrupt should be a single byte (8 bits). When accessing multiple byte single flag values (more than one byte long flags), this non-interrupt code access may be split by an interrupt response. Splitting the access may corrupt the 16 bit or greater global flag value. Non-interrupt code multiple byte single global flag access like this requires global interrupts are disabled before any access and global interrupts are restored after the access. Single byte access non-interrupt code does not require global interrupt disable/enable protection since an 8 bit AVR cannot split access to a single byte.

Never put slow code with long delays or USART output in any interrupt response code. If you are using AVR interrupt vector 19 CAN IT and you have slow interrupt response code anywhere, it will mess up the ability of vector 19 to rapidly respond to new CAN activity. For example, never use USART output debug code in any interrupt response code (this type of slow ISR debug code will cause bugs all by itself)!

Whenever CANCDMOB.IDE is masked (CANIDM4.IDEMSK=0) it adds some complexity to using the CAN hardware correctly. The only exception is the "CAN transmission after 3-bit intermission" AT90CANxxx family errata which remains simple to use. This is because this errata only re-enables the errata MOb and never uses any information from this errata MOb.

```
/* These are just C examples of some ways to code the CANIDT and CANIDM values.
   For numerically identical Tx ID values with different CAN Frame types or ID lengths:
       11 bit ID (CANCMOB.IDE=0) Data Frame (CANIDT4.RTRTAG=0) is a unique Tx ID.
       11 bit ID (CANCMOB.IDE=0) Remote Frame (CANIDT4.RTRTAG=1) is a unique Tx ID.
       29 bit ID (CANCMOB.IDE=1) Data Frame (CANIDT4.RTRTAG=0) is a unique Tx ID.
       29 bit ID (CANCMOB.IDE=1) Remote Frame (CANIDT4.RTRTAG=1) is a unique Tx ID.

All Tx Data Frame IDs sent by any CAN node MUST be unique (only be sent by that one
CAN node). Tx Remote Frame IDs do not have to be unique as long as the CANCDMOB.DLCn
value always matches. Any CAN node may Rx any ID of any type. */

/* The conditional structure of all these examples are as follows:

    #ifdef (32 bit SFIOR name)
        // Handle the entire 32 bit value with a single read or write.
    #else (this compiler does not support 32 bit SFIORs)
        // Handle the 32 bit value by reading or writing 8 bits at a time.
    #endif

If your compiler supports 32 bit SFIORs choose which one you want to use. */

//*******************************************************
// Set an 11 bit CAN Data Frame (RTRTAG=0) ID
//   - CANCDMOB.IDE bit should be cleared when CANCDMOB is written later

    unsigned int set_id_11f;         // Preset 11 bit format ID value (0x7EF max)

    CANPAGE = (mob << MOBNB0);       // Select MOb, AINC = 0, INDEX2:0 = 0

    #ifdef CANIDT
            // Set 11 bit format ID.
        CANIDT = ((unsigned long) set_id_11f << 21) | (0UL << RTRTAG);
    #else
        CANIDT1 = (unsigned char) (set_id_11f >> 3); // Set 11 bit format ID.
        CANIDT2 = (unsigned char) (set_id_11f << 5);
        CANIDT3 = 0x00;
        CANIDT4 = (0 << RTRTAG);
    #endif
    // RTRTAG (data frame = 0) and RB0TAG are both zero.

//*******************************************************
// Set an 11 bit Rx ID mask with no masked bits - 0x7FF is no mask
//   - CANCDMOB.IDE bit should be cleared when CANCDMOB is written later

    CANPAGE = (mob << MOBNB0);       // Select MOb, AINC = 0, INDEX2:0 = 0

    #ifdef CANIDM
        CANIDM = (0x7FFUL << 21) | (1UL << RTRMSK) | (1UL << IDEMSK);
    #else
        CANIDM1 = (unsigned char) (0x7FF >> 3); // No ID mask is set.
        CANIDM2 = (unsigned char) (0x7FF << 5);
        CANIDM3 = 0x00;
        CANIDM4 = (1 << RTRMSK) | (1 << IDEMSK);
    #endif

//*******************************************************
// Read an 11 bit ID value and convert it into an integer
//   - first check that the CANCDMOB.IDE bit was cleared by the RXOK

    unsigned int read_id_11f;        // Rx updated ID value when any CANIDM bits = 0

    CANPAGE = (mob << MOBNB0);       // Select MOb, AINC = 0, INDEX2:0 = 0

    #ifdef CANIDT
        read_id_11f = (unsigned int) (CANIDT >> 21);
    #else
        read_id_11f = ((unsigned int) CANIDT1 << 3) |
                      ((unsigned int) CANIDT2 >> 5);
    #endif

//*******************************************************
// Set a 29 bit CAN Data Frame (RTRTAG=0) ID
//   - CANCDMOB.IDE bit must be set when CANCDMOB is written later

    unsigned long set_id_29f;    // Preset 29 bit format ID value (0x1FBFFFFF max)

    CANPAGE = (mob << MOBNB0);   // Select MOb, AINC = 0, INDEX2:0 = 0

    #ifdef CANIDT
        CANIDT = (set_id_29f << 3) | (0UL << RTRTAG); // Set 29 bit format ID.
    #else
        CANIDT1 = (unsigned char) (set_id_29f >> 21); // Set 29 bit format ID.
        CANIDT2 = (unsigned char) (set_id_29f >> 13);
        CANIDT3 = (unsigned char) (set_id_29f >> 5);
        CANIDT4 = (unsigned char) (set_id_29f << 3) | (0 << RTRTAG);
    #endif
    // RTRTAG (data frame = 0), RB0TAG and RB1TAG are all zero.

//*******************************************************
// Set a 29 bit Rx ID mask with no masked bits - 0x1FFFFFFF is no mask
//   - CANCDMOB.IDE bit must be set when CANCDMOB is written later

    CANPAGE = (mob << MOBNB0);       // Select MOb, AINC = 0, INDEX2:0 = 0

    #ifdef CANIDM
        CANIDM = (0x1FFFFFFFUL << 3) | (1UL << RTRMSK) | (1UL << IDEMSK);
    #else
        CANIDM1 = (unsigned char) (0x1FFFFFFFUL >> 21); // No ID mask is set.
        CANIDM2 = (unsigned char) (0x1FFFFFFFUL >> 13);
        CANIDM3 = (unsigned char) (0x1FFFFFFFUL >> 5);
        CANIDM4 = (unsigned char) (0x1FFFFFFFUL << 3) | (1 << RTRMSK) |
                                  (1 << IDEMSK);
    #endif

//*******************************************************
// Read a 29 bit ID value and convert it into a long
//   - first check that the CANCDMOB.IDE bit was set by the RXOK

    unsigned long read_id_29f;       // Rx updated ID value when any CANIDM bits = 0

    CANPAGE = (mob << MOBNB0);       // Select MOb, AINC = 0, INDEX2:0 = 0

    #ifdef CANIDT
        read_id_29f = (CANIDT >> 3);
    #else
        read_id_29f = ((unsigned long) CANIDT1 << 21) |
                      ((unsigned long) CANIDT2 << 13) |
                      ((unsigned long) CANIDT3 << 5) |
                      ((unsigned long) CANIDT4 >> 3);
    #endif

// For compilers that support 32 bit AVR Special Function I/O Register (SFIOR)
// access, both types of register access are shown, except AVR instruction cycle
// efficiency varies and does not consistently favor either 32 bit or 8 bit type
// of access. Not all compilers support 32 bit SFIORs.

// The unsigned char mob value details are missing in the above code snippets.*
```

The difference between Rx General CANGIT error bits and Rx MOb CANSTMOB error bits is the CAN acceptance filter recognition (see the data sheet acceptance filter section). Any CAN Rx error that happens before the Rx acceptance filter hit will go into the General CANGIT register. Any CAN Rx error that happens after the Rx acceptance filter hit will go into the matching hit number MOb CANSTMOB register. Because a Tx MOb is required for any AVR CAN Tx, all Tx errors always go into the Tx MOb CANSTMOB register. Since the CANSMOTB.BERR bit is only a Tx error bit, there is no equivalent error bit in the CANGIT register. Errors in the General CANGIT register may be from CAN Rx activity that never matched any MOb Rx task, or may be CAN Rx activity errors early in the CAN arbitration field that made any acceptance filter hit test impossible.

The main point and intent of the acceptance filter is too screen out any Rx CAN message traffic your CAN node does not care about. This is because CAN is a broadcast bus and all CAN Tx messages are received by every CAN node. The acceptance filter hardware relieves the AVR CAN node software from the choir of having to filter out unwanted Rx CAN messages in real time. Using the Rx CANIDM1, CANIDM2, CANIDM3 and CANIDM4 mask registers allows your AVR CAN node to filter (only Rx the specific CANIDT registers and CANCDMOB.IDE ID value) or allow (mask) any/all CAN ID message traffic as desired.

An important point is the acceptance filter searches for matching enabled Rx MObs starting from the lowest number MOb group up to the highest numbered enabled Rx MOb. If a lower numbered enabled Rx MOb gets an acceptance filter match hit, then any higher numbered enabled Rx MOb that also matches will not get that acceptance filter hit. This is why the "CAN transmission after 3-bit intermission" MOb AT90CANxxx family errata, which matches every possible Rx CAN traffic (all CANIDM registers bits are zero), is always the highest numbered MOb possible. This makes the enabled errata MOb the last one searched and it only picks up any Rx CAN traffic all the other enabled Rx MObs ignored. This also means the errata MOb receives CANSTMOB errors that would have normally gone into the CANGIT register (only if the errata MOb got the match hit, otherwise early errors that make the acceptance filter hit test impossible still go into CANGIT).

If you are curious, the acceptance filter hit that happens after the live CAN data stream arbitration field ends is what drives the 19 or 39 CAN bit times to re-enable an automatically RXOK disabled Rx MOb for continuous Rx coverage. If the Rx MOb is not re-enabled before the filter hit is checked for, then that MOb will not receive the new CAN message traffic. The delay required to Rx and process the new arbitration field CAN data stream is why the Rx MOb re-enable does not have to be instant. Other ways to extend this CAN bit time limit have already been mentioned.

### This is C compiler version of the basic CAN hardware initialization code:

```
void can_init (void) {

    unsigned char mob;          // Temporary MOb register set selection number.

    // The next 3 lines of commented out code are completely optional. Do not
    //  use them unless you have a specific reason to do so.
//  CANGIE = 0;                     // Disable all CAN interrupts.
//  CANGCON = (0 << ENASTB);        // Force standby mode.
//  while (CANGSTA & (1 << ENFG));  // Wait for CAN hardware to disable.

        // Reset the CAN controller hardware and general registers.
    CANGCON = (1 << SWRES);

        // Use 6 instead of 15 for the ATmega CAN chips.
    for (mob = 0; mob < 15; mob++) {
        CANPAGE = (mob << MOBNB0);  // Set the MOb page number for each MOb.
        CANCDMOB = 0;         // Set each MOb to disabled *CRITICAL*.
        CANSTMOB = 0;         // Clear all MOb interrupt/polling flags *CRITICAL*.
    }
    // All other MOb registers only need to be setup before using the MOb.

        // Use your own values, only if you need to use another value than zero.
        // Default zero values from CANGCON.SWRES are shown.
        // Setup the CANPAGE AINC bit and INDX initial values.
//  CANHPMOB = (0 << CGP3) | (0 << CGP2) | (0 << CGP1) | (0 << CGP0);

        // Only if you use CANSTM and need to use another value than zero.
        // Default zero value from CANGCON.SWRES is shown.
//  CANTCON = 0x00;             // Set the CAN Timer Prescaler Control Register.

        // Use your own values (this is just an example).
        // Setup the CAN baud timing.
    CANBT1 = 0x12;              // Timing - See the data sheet errata if CANBT1=0.
    CANBT2 = 0x0C;              // Timing - Jump Width and Propagation.
    CANBT3 = 0x37;              // Timing - Phase Segments 2, 1 and Sample Point.

        // Use your own values (this is just an example).
        // Enable CAN IT interrupts for CANSTMOB RXOK and TXOK.
    CANGIE = (1 << ENIT) | (1 << ENRX) | (1 << ENTX);

        // Enable all the AT90CAN MObs for polling or interrupts.
    CANIE2 = 0xFF;              // Use 0x3F for the ATmega CAN chips.
    CANIE1 = 0x7F;              // Do not use this for the ATmega CAN chips.

    CANGCON = (1 << ENASTB);    // Enable the CAN and start the CANTIM counter.

    // If you wait for CANGSTA.ENFG to be set, you must provide a wait time
    // out in case the CAN fails to set ENFG.
}
```

This example is for the AT90CANxxx family CAN chips and includes comments about changes for the ATmegaxxxx family CAN chips.

### This is C compiler version of a CAN IT interrupt TXOK/RXOK/ERROR handler template:

```
#define MOB_RX_CMD      ((1 << CONMOB1) | (0 << CONMOB0))
#define MOB_TX_CMD      ((0 << CONMOB1) | (1 << CONMOB0))
#define MOB_MAX_DLC     ((1 << DLC3) | (0 << DLC2) | (0 << DLC1) | (0 << DLC0))
#define MOB_RXOK        (1 << RXOK)
#define MOB_TXOK        (1 << TXOK)
#define MOB_ENERR_FLGS  ((1 << BERR) | (1 << SERR) | (1 << CERR) | (1 << FERR) | (1 << AERR))

    // This is used to limit Rx CANCDMOB.DLC values to a maximum of 8. This is very important.
#define MOB_DLC_LIMIT(dlc) (((dlc) > MOB_MAX_DLC) ? MOB_MAX_DLC : (dlc))

INTERRUPT CAN IT () {       // Use the correct syntax for your embedded C compiler.

    unsigned char save_page;    // Pre-interrupt CANPAGE value storage.
    unsigned char mob;          // Temporary MOb number value.
    unsigned char isr_flags;    // Temporary interrupt flags value.

    save_page = CANPAGE;        // Save the pre-interrupt CANPAGE value.

        // CANGIE ENTX, ENRX and ENERR in can_init() enables the MOb interrupt
        // CAMSTMOB flags that CANSIT and CANHPMOB will respond to.
        // Only use CANPAGE = CANHPMOB one time for each MOb while loop.
        // See CANHPMOB.CGPn bits for initial CANPAGE AINC and INDX values.
        // See CANHPMOB.HPMOBn bits description for the reason 0xF0 is used.
        // The CANSIT.SITn bit must be set for CANHPMOB to select that MObn value.
    while ((CANPAGE = CANHPMOB) < 0xF0) {

  #ifdef OPTIONAL_AT90CAN_ERRATA
  //AT90CAN...ERRATA*v*v*v*v*v*v*v*v*v*v*v*v*v*v*v*v*v*v*v*v*v*v*v*v*AT90CAN...ERRATA
    // AT90CAN... errata SPY MOb (see the data sheet errata). Notice that the SPY
    // errata is handled outside of the CANHPMOB priority ordering to ensure
    // consistent fast as possible SPY errata interrupt handling.
        // A small optimization to use the correct CANSIT 8 bit register, rather than the entire 16 bit register.
      #if (SPY_MOB > 7)
        if (CANSIT1 & (1 << (SPY_MOB - 8)))     // SPY_MOB interrupt CANSIT[SPY_MOB]=non-zero.
      #else
        if (CANSIT2 & (1 << SPY_MOB))           // SPY_MOB interrupt CANSIT[SPY_MOB]=non-zero.
      #endif
        {
            // Since CANSTMOB error bits do not disable the MOb and no SPY Rx updated
            // information is ever read or used, this simplified re-enabling an
            // already enabled MOb tactic is not a problem. For normal MOb usage,
            // you would never write a Rx enable command to an already enabled MOb.
            CANPAGE = (SPY_MOB << MOBNB0);          // Select the SPY_MOB.
            CANSTMOB = 0x00;                        // Clear all of the SPY_MOB interrupt flags.
            CANIDT4 = 0x00;                         // Ensure bit 1 is cleared in case a RXOK randomized it.
            CANCDMOB = MOB_RX_CMD | MOB_MAX_DLC;    // Re-enable the SPY MOb Rx (as shown in the data sheet).
            continue;                               // The SPY_MOB has no Rx info to process.
        }
  //AT90CAN...ERRATA*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*AT90CAN...ERRATA
  #endif

            // Extract the MOb number value of the MOb being processed.
        mob = (CANPAGE >> MOBNB0);
        isr_flags = CANSTMOB;         // Save the MOb interrupt flags state.
            // Clear the MOb interrupt flags when you process each MOb. This also
            // clears the read only CANSIT.SITn bit for this MOb number n (now
            // CANHPMOB will ignore this MOb when the CANSIT.SITn bit is cleared).
        CANSTMOB = 0;                 // Immediately clear the flags.

        // ******* process this active CANSTMOB interrupt MOb number *******
        // You must use isr_flags since CANSTMOB was cleared.
        if (isr_flags & MOB_TXOK) {       // Only if CANGIE.ENTX is set.
            // Process MOb number mob TXOK activity. Add your code here.
        }
        if (isr_flags & MOB_RXOK) {       // Only if CANGIE.ENRX is set.
            // Process MOb number mob RXOK activity. Add your code here.
            // Always use MOB_DLC_LIMIT(CANCDMOB.DLC) to get the DLC value.
        }
        if (isr_flags & MOB_ENERR_FLGS) { // Only if CANGIE.ENERR is set.
            // Process any isr_flags error bits here (if you care).
            // Optional: recover any wiped out TXOK, RXOK or DLCW bits in isr_flags (see below).
        }

    } // ===> end of the while(CANHPMOB) MOb processing loop <===

    // CANGIE in can_init() selects the enabled General interrupt flags.

        // First save and then clear the general interrupt flags.
    isr_flags = CANGIT;         // Save the current general interrupt flags state.
        // OVRTIM does not belong to this CAN IT interrupt vector.
        // Using isr_flags instead of CANGIT prevents clearing any new interrupts.
        // Clear only the General interrupt flags that will be processed next.
    CANGIT = isr_flags & ~(1 << OVRTIM);

    // ***** process all enabled general CANGIT interrupts using isr_flags *****
    // An example of using isr_flags instead of CANGIT would be:
    //  if (isr_flags & (1 << BOFFIT)) - CANGIT is not used since it was cleared.

    CANPAGE = save_page;        // Restore the pre-interrupt CANPAGE value.
}
```

How you process each MOb TXOK or RXOK is up to you. For example the RXOK may immediately extract MOb information, or it may set a volatile global software variable so that non-interrupt code may detect and process the RXOK activity and extract the MOb information later.

When using the AT90CAN... family ERRATA, the SPY_MOB number is always the highest numbered MOb used (usually MOb number 14 decimal - the 15th MOb). Remove this AT90CAN... ERRATA code if you are using the ATmega.... family CAN chips.

If CANGIE.ENERR is set, the required CANSTMOB=0 clear of the error bits could under very rare circumstances wipe out a new CANSTMOB RXOK, DLCW or TXOK. There is a fix for this very rare bug that is not shown in this simple typical use example. These two sequential operations make it possible to test for this problem:

```
isr_flags = CANSTMOB;     // Save the MOb interrupt flags state. - First operation
CANSTMOB = 0;             // Immediately clear the MOb interrupt flags. - Second operation
    // Test for unexpectedly disabled MOb here.
    // The MOb CANCDMOB.CONMOBn MOb command bits are not set to disable the MOb...
    // The MOb CANEN busy bit is cleared...
    // The CANGCON.ABRQ bit is not set...
    // The CANGCON.ENASTB is still set...
        // If all these tests are true, use the CANCDMOB.CONMOBn MOb command bits
        // to determine if a TXOK or RXOK was lost and correct isr_flags. This does
        // not work if the CANCDMOB.RPLV bit was set. If you want to recover the
        // CANSTMOB.DLCW bit, you will need a saved copy of the original CANCDMOB.DLC
        // value. If the CANGCON.ABRQ is set outside the interrupt code, make sure
        // all MOb CANCDMOB.CONMOBn MOb command bits are set to disable before clearing
        // the CANGCON.ABRQ bit (disable AVR interrupts during the ABORT).
        // This way a CAN IT interrupt response after the ABRQ event will
        // not accidentally cause a false unexpected disable detection here.

        // If CANGCON.TTC is set do not make any TXOK corrections.
```

If isr_flags has any error bits set and the MOb is disabled (CANENn bit n is cleared) for no known reason, indicates a RXOK or TXOK flag was wiped out. Quickly responding to and clearing CANSTMOB errors reduces this rare bug risk. When CANGIE.ENIT is set, quick response requires correctly implemented AVR interrupts. Any AVR interrupts that are very slow to execute could prevent a quick response. For example: a typical beginner mistake of putting USART output debug code in an interrupt response may easily cause very significant response delays (this type of slow USART debug code in an ISR typically breaks the program and creates bugs all by itself).

When in TTC mode a Tx will not have any automatic retries and it will disable itself when it gets any Tx error. This TTC mode Tx behavior mimics the non-TTC mode TXOK flag write CANSTMOB conflict problem, so this conflict correction does not work for Tx in TTC mode.

In order for this rare bug to happen the sequence timing is: after the CANSTMOB read with only error flag bits set (first operation), the CAN hardware sets a TXOK, RXOK or DLCW in CANSTMOB and then the following software CANSTMOB=0 (second operation) wipes out these new TXOK, RXOK or DLCW bits without ever knowing they were just set. This is why the CANSTMOB read must be immediately followed by the CANSTMOB=0. This immediate paring minimizes the window of opportunity for this bug to occur. Since an entire error free CAN frame is required for TXOK or RXOK to be set after the last error CAN frame, this bug requires a significant delay in processing the TXOK or RXOK event after an error. This is why rapid responses to any CANSTMOB error flags is the first/best defense for preventing this bug. This bug is rare because of the complex trigger conditions and extremely tight timing it needs to occur, but rare does not mean impossible and in this case rare means not reproducible if you are trying to debug it!

Edit: 9-28-2012 added new TTC information.
