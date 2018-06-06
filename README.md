**Qt - Bitcoin/Dogecoin API interaction**

Simple use of the Dogecoin core API from Qt without any dependencies

**Example usage**

    BitcoinCore core("DogecoinRPCUser", "DogecoinRPCPassword"); 
    
    core.getbalance("Kevin");
    core.getbalance();
    core.sendfrom("Kevin", "DJVUbtMvoyxNUHHriNpyNYpMA4MEW9bb1H", 2); // Sends 2 Dogecoin from account Kevin

**Functions**

    void getbalance( const QString username = {} ); // gets the user balance or the wallet balance of all users
    bool sendfrom( const QString username, const QString walletAddress, const qint32 amount ); // Send from user to address amount XYZ. For Bitcoin it's recommended to use a double instead of qint32.

More functions can be easily integrated. 

