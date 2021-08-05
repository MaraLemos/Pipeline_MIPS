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

  //WB
  int RegWrite;
  int MemtoReg;
  //M
  int Branch;
  int MemRead;
  int MemWrite;
  //EX
  int regDst;
  int ALUOp1;
  int ALUOp0;
  int ALUSrc;
};

struct EX_MEM{
	int pc;
  int rd_rt;
  int ALU_result;
  int ALU_zero;
  int datart;

  //WB
  int RegWrite;
  int MemtoReg;
  //M
  int Branch;
  int MemRead;
  int MemWrite;
};

struct MEM_WB{
  int pc;
  int rd_rt;
  int ALU_result;
  int data;

  //WB
  int RegWrite;
  int MemtoReg;
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
    int jump;
};
