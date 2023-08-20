#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#define MAX 10
using namespace std;

//divisão
//fibonacci


int main() {

int x=0, y=-1, aux=0, numero, operandos[MAX];
char linha[MAX], operador[MAX];
ofstream out;

out.open("Cod_Gerado.asm");

    ///////////////////////////////////
    //    Leitura dos dados          //
    ///////////////////////////////////

    cout << "Digite sua equacao ('e' para encerrar): ";
    do {

        cin >> linha;

        if (linha[0] == '+' || linha[0] == '-' || linha[0] == '*' ||linha [0] == '/' ||linha[0] == 'r' ||linha[0] == '^'||linha[0] == '!' || linha[0] == 'f'){
           //armazena no vetor de operandos
            y++;
            operador[y] = linha[0];
        }

        else //armazena no vetor de operações
	    {
	        //////////////////////////////////////////
	        //  Tratando caso seja número negativo  //
	        //////////////////////////////////////////

            if (linha[0] == 'n'){
                for (aux = 0; aux < 10; aux ++)
                    linha[aux] = linha [aux+1];
                numero = atoi(linha);
                numero = -numero; //torna o numero negativo
            }
            else
                numero = atoi(linha);

            operandos[x] = numero; // empilha
            x++; // aumentando índice da pilha
	    }

    }while  ((linha[0] != 'e') && (x < MAX) && (y < MAX));

    ///////////////////////////////////
    // Escrita dos dados no arquivo  //
    ///////////////////////////////////
    out<< ".data" << endl;
    out << "error_msg: .asciiz \"Não foi possivel calcular\" "<< endl;
    out <<"num: .word "; //fila dos operandos
    for (aux =0; aux < x-1; aux++)
        out << operandos[aux] << ","; //fila dos operandos
    out <<endl <<endl <<".text "<< endl;
    out << " main:"<< endl;
    out << "la      $t0, num" <<endl;

    aux=0;

    while (aux <= y){ //chamada de funções do main principal

        if (operador[aux] == '+')
            out << "jal    main_add"<<endl;
        else if (operador[aux] == '-')
            out << "jal    main_sub"<<endl;
        else if (operador[aux] == '*')
            out << "jal    main_mult"<<endl;
        else if (operador[aux] == '/')
            out << "jal    main_div"<<endl;
        else if (operador[aux] == 'r')
            out << "jal    main_raiz"<<endl;
        else if (operador[aux] == '^')
            out << "jal    main_potencia"<<endl;
        else if (operador[aux] == '!')
            out << "jal    main_fatorial"<<endl;
        if (operador[aux] == 'f')
            out << "jal    main_fibonacci"<<endl;
        aux++;
    }

    out << "jal     exit"<<endl<<endl;

    ///////////////////////////////////////////////
    ////////            FUNÇÕES            ////////
    ///////////////////////////////////////////////


    // ADIÇÃO
    out <<"main_add:"<<endl;
    out << "lw      $s0, 0($t0)" <<endl;
    out << "lw      $s1, 4($t0)"<<endl;
    out << "add     $s2 $s0 $s1"<<endl;
    out << "sw      $s2, 4($t0)" <<endl;
    out << "addi    $t0 $t0 4"<<endl;
    out << "jr    	$ra"<<endl<<endl;


    // SUBTRAÇÃO
    out << "main_sub:"<<endl;
    out << "lw      $s0, 0($t0)" <<endl;
    out << "lw      $s1, 4($t0)"<<endl;
    out << "sub     $s2 $s0 $s1" <<endl;
    out << "sw      $s2, 4($t0)" <<endl;
    out << "addi    $t0 $t0 4"<<endl;
    out << "jr    	$ra"<<endl<<endl;


    // MULTIPLICAÇÃO
    out << "main_mult:" <<endl;
    out << "lw      $s0, 0($t0)" <<endl;
    out << "lw      $s1, 4($t0)"<<endl;
    out << "mul     $s2, $s0, $s1" <<endl;
    out << "sw      $s2, 4($t0)" <<endl;
    out << "addi    $t0 $t0 4"<<endl;
    out << "jr    	$ra"<<endl<<endl;


    // DIVISÃO
    out <<"main_div:"<<endl;
    out << "lw      $s0, 0($t0)" <<endl;
    out << "lw      $s1, 4($t0)"<<endl;
    out << "div     $s2, $s0, $s1" <<endl;
    out << "sw      $s2, 4($t0)" <<endl;
    out << "addi    $t0 $t0 4"<<endl;
    out << "jr    	$ra"<<endl<<endl;


    // RAÍZ QUADRADA
    out <<"main_raiz:" <<   endl;
    out <<"lw       $s0, 0($t0)" <<endl;
    out <<"li       $s2, 0" <<   endl;
    out <<"isqrt:" <<    endl;
    out <<"mul      $t2, $s2, 2" <<   endl;
    out <<"add      $t2, $t2, 1" <<   endl;
    out <<"sub      $s0, $s0, $t2" <<   endl;
    out <<"add      $s2, $s2, 1" <<   endl;
    out <<"beq      $s0, $zero, success" <<   endl;
    out <<"slt      $t2, $s0, $zero" <<   endl;
    out <<"beq      $t2, 1, error" <<   endl;
    out <<"j        isqrt" <<   endl;
    out <<"success:" <<endl;
    out <<"sw        $s2, 0($t0)" <<   endl;
    out << "jr    	$ra"<<endl<<endl;


    // POTENCIAÇÃO
    out << "main_potencia:"<<endl;
    out << "lw      $s0, 0($t0)" <<endl;
    out << "lw      $s2, 0($t0)" <<endl;
    out << "lw      $s1, 4($t0)"<<endl;
    out << "li      $t2,1" <<endl;
    out << "while:" <<endl;
    out << "beq      $t2,$s1,fim" <<endl;
    out << "mul      $s2,$s2,$s0" <<endl;
    out << "add      $t2,$t2,1" <<endl;
    out << "j        while" <<endl;
    out << "fim:" <<endl;
    out << "sw      $s2,4($t0)" <<endl;
    out << "add     $t0, $t0, 4" <<endl;
    out << "jr    	$ra"<<endl<<endl;


    // FATORIAL
    out << "main_fatorial:" <<   endl;
    out << "lw	    $s2, 0($t0)" <<endl;
    out << "lw	    $t1, 0($t0)	" <<endl;
    out << "beqz    $s2, error" <<endl;
    out << "bltz    $s2, error" <<endl;
    out << "fact: " <<endl;
    out << "subi    $t1, $t1, 1" <<endl;
    out << "beqz    $t1, end" <<endl;
    out << "mul     $s2, $s2, $t1 " <<endl;
    out << "sw      $s2, 0($t0)" <<endl;
    out << "j 	    fact " <<endl;
    out << "end:" <<endl;
    out << "sw      $s2,0($t0)" <<endl;
    out << "jr    	$ra" <<endl<<endl;


    //  FIBONACCI
	out <<"main_fibonacci:" <<   endl;
	out <<"lw 	    $t2, 0($t0)" <<   endl;
	out <<"blez 	$t2, error" <<   endl;
	out <<"li	    $s3, 1" <<   endl;
	out <<"li 	    $s4, 1" <<   endl;
	out <<"add 	    $s5 $s3 $s4" <<   endl;
	out <<"addi 	$t2, $t2, -3" <<   endl;
	out <<"sw 	    $s5, 0($t0)" <<   endl;
	out <<"la       $s2, ($s5)" <<   endl;
	out <<"j        Loop" <<   endl;
	out <<"fim_i:" <<   endl;
	out <<"jr 	    $ra" <<   endl;
	out <<"Loop:" <<   endl;
	out <<"add	    $s3, $s5, $s4" <<   endl;
	out <<"addi 	$t2, $t2, -1" <<   endl;
	out <<"sw	    $s3, 0($t0)" <<   endl;
	out <<"la       $s2, ($s3)" <<   endl;
	out <<"blez 	$t2,  fim_i" <<   endl;
	out <<"add	    $s4, $s5, $s3" <<   endl;
	out <<"addi 	$t2, $t2 -1" <<   endl;
	out <<"sw	    $s4, 0($t0)" <<   endl;
	out <<"la       $s2, ($s4)" <<   endl;
	out <<"blez 	$t2, fim_i" <<   endl;
	out <<"add	    $s5 $s4 $s3" <<   endl;
	out <<"sw   	$s5 0($t0)" <<   endl;
	out <<"la       $s2, ($s5)" <<   endl;
	out <<"addi 	$t2, $t2, -1" <<   endl;
	out <<"blez 	$t2, fim_i" <<   endl;
	out <<"bgtz 	$t2, Loop" <<   endl;


    //////////////////////////////////
    //   Impressão do resultado     //
    //////////////////////////////////

    out << endl << "exit: ";
    out << endl << "la       $a0, ($s2)";
	out << endl << "li      $v0,1";
	out << endl << "syscall";
	out << endl << "li      $v0, 10";
	out << endl << "syscall"<<endl<<endl;

    out <<"error:" <<   endl;
    out <<"la       $a0, error_msg" <<   endl;
    out <<"la       $v0, 4" <<   endl;
    out <<"syscall" <<   endl;

out.close();

cout<<"\nArquivo Criado!";
}
