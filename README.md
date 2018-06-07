**Qt - Bitcoin/Dogecoin API interaction**

Simple use of the Dogecoin core API from Qt without any heavy JSON-RPC dependencies

**Example usage**

    BitcoinCore core("DogecoinRPCUser", "DogecoinRPCPassword"); 
    
    core.getbalance("Kevin");
    core.getbalance();
    core.sendfrom("Kevin", "DJVUbtMvoyxNUHHriNpyNYpMA4MEW9bb1H", 2); // Sends 2 Dogecoin from account Kevin
    core.gettransaction("3d0581d05cb8869f40085217b1cee7b58ec70a35ad11a807e1c74808c0151c3b");
    core.getnewaddress();
    core.getnewaddress("Mike"); // Create a new address for user Mike
  

