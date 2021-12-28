# Small Standard Cell Library
Designing and characterizing a small standard cell library using Electric.
### 1.1 Stick Diagrams
- The stick Diagrams for the basic cells (NOT, NAND, NOR):


  ![alt text](https://github.com/Iman-7/Small-Standard-Cell-Library/blob/main/1.PNG)

- The stick Diagram for the complex function (g(x,y,z) = ~(xy+ xz+ yz)):
   ![alt text](https://github.com/Iman-7/Small-Standard-Cell-Library/blob/main/2.PNG)

### 1.2 Calculations of Cells’ heights
a. For the inverter:
- Size 1: width of the pmos = 1*Kp*Wmin = 1 x 2.3 x 3 = 6.9 = 7𝛌, width of
nmos = 1*Wmin = 3 𝛌, So, H = 8 + 7 + 12 + 3 + 8 + 4 = 42 𝛌
- Size 2: width of the pmos = 2*Kp*Wmin = 2 x 2.3 x 3 = 13.8 = 14𝛌, width
of nmos = 2*Wmin = 6 𝛌, So, H = 8 + 14 + 12 + 6 + 8 + 4 = 52 𝛌
- Size 4: width of the pmos = 4*Kp*Wmin = 4 x 2.3 x 3 = 27.6 = 28𝛌, width
of nmos = 4*Wmin = 12 𝛌, So, H = 8 + 28 + 12 + 12 + 8 + 4 = 72 𝛌
- Size 8: width of the pmos = 8*Kp*Wmin = 8 x 2.3 x 3 = 55.2 = 56𝛌, width
of nmos = 8*Wmin = 24 𝛌, So, H = 8 + 56 + 12 + 24 + 8 + 4 = 112 𝛌

b. For the 2 input NAND gate:
- Size 1: width of the pmos = 1*Kp*Wmin = 2.3 x 3 = 6.9 = 7𝛌, width of
nmos = 1*2*Wmin = 6 𝛌, So, H = 8 + 7 + 8 + 4 + 6 + 8 + 4 = 45𝛌
- Size 4: width of the pmos = 4*Kp*Wmin = 4 x 2.3 x 3 = 27.6 = 28𝛌, width
of nmos =8*Wmin = 24 𝛌, So, H =8 + 28 + 8 + 4 + 24 + 8 + 4 = 84 𝛌

c. For the 2 input NOR gate:
- Size 1: width of the pmos = 2*Kp*Wmin = 2 x 2.3 x 3 = 13.8 = 14𝛌, width
of nmos = 1*Wmin = 3 𝛌, So, H = 8 + 14 + 8 + 4 + 3 + 8 + 4 = 49𝛌
- Size 4: width of the pmos = 8*Kp*Wmin = 8 x 2.3 x 3 = 55.2 = 56𝛌, width
of nmos = 4*Wmin = 12 𝛌, So, H =8 + 56 + 8 + 4 + 12 + 8 + 4 = 100 𝛌

d. For the Complex function g(x,y,z) = ~(xy+xz+yz)
- Size 1: width of the pmos = 2*Kp*Wmin = 2 x 2.3 x 3 = 13.8 = 14𝛌, width
of nmos = 2*Wmin = 6 𝛌, So, H = 8 + 14 + 8 + 8 + 8 + 4 + 6 + 8 + 4 = 68𝛌
- Size 4: width of the pmos = 8*Kp*Wmin = 8 x 2.3 x 3 = 55.2 = 56𝛌, width
of nmos= 8*Wmin = 24 𝛌, So, H = 8 + 56 + 8 + 8 + 8 + 4 + 24 + 8 + 4 =
128𝛌

Important Remark: We have chosen the standardized height for all the cells in our library
to be 68𝛌.

### 1.3 Procedures & Implementation
We start by specifying the characteristics that we should declare in order to make the
correct schematics and layouts for the cells.
- We determined the design rules for widths and lengths
- Wmin = 3 𝛌
- Lmin = 2 𝛌
- Minimum contact area = 4 * 4 𝛌
- Spacing between two polysilicon = 3 𝛌
- Width of VDD & GND = 4 𝛌
- After that, we moved forward and drew the stick diagram for each cell to help us on the layout design, in addition to calculating the width of each transistor in each cell to fit the required size for this cell.
- For example, if we have two connected resistors in series in one network, and it’s required to make the cell of size 2. So, after searching on the worst case, we will seek to make the two transistors have total resistance equal 2. Then we increase the width of each one by 2 to decrease the resistance. Hence, if it was in the pull-down network, the width of the NMOS will be 4 * 2.3 𝛌
- Second, we calculate the expected height for each cell by measuring the minimum possible spacing between components. While building the designs, we should determine a fixed number for the cell height, which we choose 78 𝛌.
- If the height exceeds this number, then folding must be done, which means splitting any long PMOS or NMOS to several or parallel resistances dividing the width of the original transistor.
- The following table shows the resulting height and width for every cell in our library. The height should be a fixed number and the width should be a multiple of 8.
| Cell  | Height | Width |
| ------------- | ------------- |------------- |
| NOTx1  | 79  | 32  |
| NOTx2   | 79 | 32  |
| NOTx4  | 79  | 56  |
| NOTx8   | 79 | 88  |
| NORx1  | 79  | 40  |
| NORx4   | 79 | 88  |
| NANDx1  | 79  | 40  |
| NANDx4   | 79 | 88  |
| gx1  | 79  | 104  |
| gx4   | 79 | 344  |
