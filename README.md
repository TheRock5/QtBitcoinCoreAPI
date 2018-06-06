**Qt - Bitcoin/Dogecoin API interaction**

Simple use of the of Dogecoin core API from Qt without any dependencies

**Example usage**

    BitcoinCore core("DogecoinRPCUser", "DogecoinRPCPassword"); 
    
    core.getbalance("Kevin");
    core.getbalance();
    core.sendfrom("Kevin", "DJVUbtMvoyxNUHHriNpyNYpMA4MEW9bb1H", 2); // Sends 2 Dogecoin from account Kevin



