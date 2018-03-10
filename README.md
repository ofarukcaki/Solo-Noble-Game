# Solo Noble Game

> Marmara University Faculty of Engineering 
> CSE225/CSE2025 Data Structures Project 
> Ömer Faruk Çakı 
> 09.03.2018

## Project Description
In this project, you are expected to develop a program in C programming language that imitates the game known as “SOLO NOBLE”, using linked list data structure.

### How to play the game
Game board is an n*n sized matrix as illustrated in Figure 1 (n shall be an even number). The specialized game fills the entire board with pegs except for the central four holes. The objective is, making valid moves, to empty the entire board.
You can see a board of size 8*8 below. An example move is shown in Figure 2; peg located in D2 aimed to move to D4, peg in D3 cell will be removed by this movement (Figure 3). Another move is given in Figure 4; the peg in B2 cell aimed to move to D2, peg in C2 cell will be removed by this movement (Figure 5).
![enter image description here](https://i.hizliresim.com/kOpPXJ.png)

### Application Details
You are supposed to use n linked lists in the implementation (n is the input size given by the user). Each linked list node
will correspond to a cell on the board that has peg on. You should not store the empty cells.
The nodes of the linked lists must include at least the location (A1, A2, .., B1, B2,…) and the next node information.
Additionally, the header nodes of the linked lists should also be connected in a linked list. That is, the header nodes
should also have the information for the header of the next linked list. Your multi-linked list structure will be similar
with the illustration in Figure 6. Corresponding game board is shown in Figure 7.
![enter image description here](https://i.hizliresim.com/9mABN8.png)
Game will be played in C command window; application interface must be prepared properly like in Figure 8 and Figure
9.
![enter image description here](https://i.hizliresim.com/qGpXvq.png)


## Screenshot:

![enter image description here](https://lh3.googleusercontent.com/h0Vvp_GK89PnPh3q8aRXYrdDnL4vMltJ_MeDhcmkocxxb_JPyw8FfIZiK6W8ms_JD96A5_cCS_6DoiPJS2qoXPmC3aUwDRdYc3y8f1GLCtkxolgmKnIPIdRJAb5FQAjn_PhxnESnD7qGW2WtM6j9bNkfIcuSAzQ2qIJnAINwnlwuXRKMFLhiVll4yeEYojfe8V5vnG4TMk1tIxF4rcRyRW_j4Lrgq1P7CE-MqAp3BVgppSFecXpykMhcnC3mV41W1QcoVj6yJMDDm5VjC5tw0dwRx-IFFgjh3n7h__NZ5aDLFVG3lq24vSJi837HTrLlFEo4OqIZ2WEHMwVdAZ-vgtBblv2KgP_GeRK3hV-N2_YSel1G8sWRKaqF7olOdZe7kmPwNRUe4gefnVmG-L6EoW4neGOmr-x-GwV37NXLFCdnzmRArLnc1T0Uu2hDEctNHpI8u61aQCOjKgkIdTHyTk-OtA1ou5pQy8Ooic4u8Y7MCJG1mQVHRkXrxdMqdqT81-OXR6jOxm_dr1Lg4kyBroewzn1I8DrfNo-tg-xPjkn0I1DMQngXbI7IGfyk4O8b2l_XMgb0utatMfnYyx16Og42J3SLufMAdbUSr708X3VBDfU_PaG6cgI7sbiTPDsHUH5N2QH0XMfwMq7rNMmV2eA5ECzhrJyx=w740-h459-no)

