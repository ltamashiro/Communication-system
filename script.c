void segura(void) //Função que espera a volta do acelerômetro para a posição repouso 
{
	while(count == 0)
	{	
	leitura();// Função de leitura do acelerômetro
		if(ang_X > -1 && ang_X < 1 && ang_Y > -1 && ang_Y < 1 && ang_Z > -80 && ang_Z < -75)
		{
			//repouso = 1;
			count =1;
			direita = 0;
			esquerda = 0;
		}
	}
}

void putcharBT(char c) //Envia um char
{
	BT1_SendChar(c);
}


void putstringBT(char string[]) { //Recebe uma string e imprime caracteres, um a um
    
    int i = 0;
    while (string[i])
    {
        putcharBT(string[i]);
        i++;
    }
    
}

void pulalinha()
{
	BT1_SendChar('\n'); // Envio de caractere para pular linha o celular
	BT1_SendChar('\n');
	BT1_SendChar('\r'); // Retorno para o inicio da proxima linha
}



void menu1(void)
{   
	putstringBT("Instrucoes");
	pulalinha();
	putstringBT("-> NAO");
	pulalinha();
	putstringBT("<- SIM");
	pulalinha();
	putstringBT("^ mais opcoes");
	pulalinha();
}

void menu2(void)
{
		pulalinha();
		putstringBT("Instrucoes");
		pulalinha();
		putstringBT("-> Banheiro");
		pulalinha();
		putstringBT("<- Fome");
		pulalinha();
		putstringBT("^ Sede");
		pulalinha();
}



void TI1_OnInterrupt(void)
{
 
	while(k==0)
	{
		menu1();
		k=1;
	}
	leitura();//Função de leitura do acelerômetro
	segura();

	//as flags direita, cima e esquerda servem para sinalizar que o comando ja foi reconhecido e evitar que a instrucao seja repetida infinitas vezes.
	
	//Menu instruções: torção para direita (NÃO)
	if(ang_X > 0 && ang_X <  5 && ang_Y > 40 && ang_Z <0 && direita ==0 && necessidade ==0 ) 
	{
		putstringBT("NAO");
		pulalinha();
		direita  = 1;
		esquerda =0;
		cima =0 ;
		count = 0;
		}
		
	
	//Menu instruções: torção para esquerda (SIM)
	if(ang_X > 0 && ang_X <  5 && ang_Y < -18 && ang_Z > -60 && ang_Z< -40 && esquerda ==0 && necessidade ==0) 
		{
		
			putstringBT("SIM");
			pulalinha();
			esquerda=1;
			cima =0 ;
			direita =0;
			count =0;
		}
		
	 //Menu instruções: torção para cima (Necessidades)
		if(ang_X > 20 && ang_Y > 0 && ang_Y < 10 && ang_Z <-40 && cima ==0 && necessidade ==0) 
		{
			menu2();
			pulalinha();
			esquerda=0;
			direita=0;
			necessidade = 1; // flag que possibilita o acesso ao segundo menu
			count=0;
							
		}
		
		segura();
		//Menu Necessidades: torção para esquerda (Alimentação)
		if(ang_X > 0 && ang_X <  5 && ang_Y < -18 && ang_Z > -60 && ang_Z< -40 && esquerda ==0 && necessidade==1) 
		{
		
			putstringBT("Estou com fome!");
			pulalinha();
			esquerda =1;
			direita=0;
			cima=0;
			necessidade=0;
			count=0;
			
		}

		//Menu Necessidades: torção para direita (Banheiro)
		if(ang_X > 0 && ang_X <  5 && ang_Y > 40 && ang_Z <0 && direita ==0 && necessidade==1) 
		{
			putstringBT("Quero ir ao banheiro");
			pulalinha();
			esquerda = 0;
			direita =1;
			cima=0;
			necessidade=0;
			count=0;
			
		}
		
		//Menu instruções: torção para cima (Necessidades)
		if(ang_X > 20 && ang_Y > 0 && ang_Y < 10 && ang_Z <-40 && cima ==0 && necessidade ==1) 
		{
			
			putstringBT("Tenho Sede");
			pulalinha();
			esquerda=0;
			direita=0;
			cima=0;
			necessidade=0;
			count=0;
		
		}		
			
}
