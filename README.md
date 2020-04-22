# btcmon - very small cryptocurrency monitor

This is a super small windows app to show you the current price of any crypto. 
It pulls it from api.cryptowat.ch/markets/coinbase-pro/btcusd/price , 
which can be changed to another API or currency (default is BTC/USD)
It will update as the window title text (including when minimized)

<b>Why?</b>
(other than 'I got bored')

RAM usage:
this app < 3MB
cryptowat.ch on a browser > 20MB (just for that tab) 

Compiling  

Required libraries:
C++ Requests : https://whoshuu.github.io/cpr/

