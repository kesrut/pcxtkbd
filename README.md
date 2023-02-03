# pcxtkbd

PS/2 -> PC/XT Arduino based Keyboard adapter originally by kesrut. 
This version has IO changed to "open collector" to minimize the risk on shorting pins by mistake(frying the XT) and to conform with standard. 

Original version also had an issue that would cause an IBM XT to enter "Manufacturing mode" after POST so keyboard would only work 50% of the time in Cassette Basic. 

Video about the subject, including the issues mentioned above and the different keyboard protocols:
Building an IBM PC XT from SCRATCH
https://youtu.be/fGLiPh0byCo

Please add https://github.com/techpaul/PS2KeyAdvanced Arduino library to compile.

Information: http://www.ccgcpu.com/2019/02/14/the-xt-part-4-adapting-a-modernish-keyboard/
