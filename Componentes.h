struct IF_ID{
	int pc;
	long int instrucao;
};

struct ID_EX{
	int pc;
	int rd;
	int rt;
	int datars;
	int datart;
	int constant_or_address;
};

struct EX_MEM{
	
};

struct MEM_WB{

};

struct Control
{
    int regDst;
    int ALUOp1;
    int ALUOp0;
    int ALUSrc;
    int Branch;
    int MemRead;
    int MemWrite;
    int RegWrite;
    int MemtoReg;
};