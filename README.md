**Qt - Bitcoin/Dogecoin API interaction**

Simple use of the of the Bitcoin, Dogecoin, etc. core APIs without any dependencies

**Example usage**

    BitcoinCore core("DogecoinRPCUser", "DogecoinRPCPassword");
    core.getbalance("Kevin");
    core.getbalance();
    core.sendfrom("Kevin", "DJVUbtMvoyxNUHHriNpyNYpMA4MEW9bb1H", 2);



