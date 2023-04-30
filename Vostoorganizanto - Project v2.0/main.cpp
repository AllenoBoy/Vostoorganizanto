/* DOCUMENTA��O DO C�DIGO |||||||||| <EXCLUSIVO PARA AP1>
---------------------------------------------------------
  # VOSTOORGANIZANTO - UM ORGANIZADOR DE FILAS PR�TICO: {
    $ LINGUAGEM BASE UTILIZADA - C
    $ WIN 32 GUI PROJECT
    $ BIBLIOTECA windows.h
    $ VOSTOORGANIZANTO - Organizador de Filas em PT-BR
                                                        }
---------------------------------------------------------
  # SOFTWARES UTILIZADOS:                               {
    $ CODE::BLOCKS
    $ ResEdit
    $ Dev-C++
                                                        }
---------------------------------------------------------
  # DISCIPLINA DE ALGORITIMOS E PROGRAMA��O I:          {
    $ PROJETO FINAL DA DISCIPLINA
    $ DOCENTE: ANA PAULA FREITAS VILELA BOAVENTURA
    $ DISCENTES:{ ALLISON DANTAS - 202200132
                  FABIO CASTRO   - 202201161
                  LETICIA        - 202200160
                  ...
                }
                                                        }
---------------------------------------------------------
*/

/// AQUI COME�A O C�DIGO

/// BIBLIOTECAS UTILIZADAS
    #include <stdio.h>
    #include <stdlib.h>
    #include <windows.h>
    #include <commctrl.h>
    #include <locale.h>
    #include <string.h>
    #include <sys/stat.h>

/// HEADER QUE ORGANIZA OS IDS PARA CHAMADA DE DIALOGOS E FUNCIONALIDADES DOS BOT�ES ///
    #include "resource.h"

/// PONTEIRO DE CONTROLE DO ARQUIVO QUE VAI ARMAZENAR A FILA
    FILE *fila;

/// FUN��ES

void changeDialogTest() {Beep(256, 200);}
void changeDialogSound() { Sleep(10); Beep(300, 170); }
void notWrong() { Beep(440, 223); }

/// VARI�VEIS UTILIZADAS GLOBALMENTE
// OBS.: N�o � interessante comentar sobre cada uma no c�digo d� para entender.
    int entrarFila, controle = 1, vamosAddPeople, podeAcessar = 0, filaCriada, isCreatedQueue = 0, isToDelete, isToCorrect, setColore;
    char filaNameValidation[1024*9], lista_formatada[1024*100], isEmpty[2] = " ", numeroDaQueue[1024*10];

/// IDENTIFICADOR PARA UMA INST�NCIA, OU SEJA CRIAR JANELAS, BOT�ES, ETC.
    HINSTANCE hInst;

/// AQUI � ONDE CONTROLAMOS AS FUN��ES, BOT�ES, TEXTOS, DIALOGOS, ARQUIVOS, DO NOSSO C�DIGO.
/// !!! O QUE EXECUTA PRIMEIRO � A FUN��O INT DO FINAL QUE EXECUTA E DEPOIS CHAMA ESSA FUN��O !!!
BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch(uMsg)        /// SWITCH QUE CHAMA O uMsg <respons�vel por tudo que o programa ir� mostrar para a gente>
    {
    case WM_INITDIALOG: /// DEFINE O QUE ACONTECE TODA VEZ QUE ABRE UM DIAL�GO
        {} return TRUE; /// !!PRECISA SER VERDADEIRO, SE N�O UM ERRO OCORREU!!

    case WM_CLOSE:      /// DEFINE O QUE ACONTECE TODA VEZ QUE FECHA UM DIAL�GO
    {
EndDialog(hwndDlg, 0);  /// FECHA O DIAL�GO
    } return TRUE;      /// !!PRECISA SER VERDADEIRO, SE N�O UM ERRO OCORREU!!

case WM_COMMAND:
                 /// AQUI EST�O OS COMANDOS QUE SER�O EXECUTADOS
{                /// OU SEJA TODA A FUNCIONALIDADE DO C�DIGO, CASO TAL BOT�O SEJA APERTADO, OU N�O
                 /// EXISTA ALGO, EMITA ALGO, MUDE ALGO, ETC.

switch(LOWORD(wParam)) /// SWITCH QUE CASO N�O DE ERRO EXECUTE O QUE FOI PROGRAMADO

{/// COME�O DA DECLARA��O DE COMANDOS

///<---------------------------------------------------------------------------------------------------->

/// BOT�O DE RETORNO PARA O MENU | BTN_RETURN |

case BTN_RETURN: {      // CASO SEJA PRESSIONADO
system("cls"); //limpa a tela do console
EndDialog(hwndDlg, 0);  // FECHA O DIAL�GO ATUAL, E NA LINHA ABAIXO CHAMA O DIAL�GO IDD_MENU

changeDialogSound(); /// beep decorativo

return DialogBoxA(hInst, MAKEINTRESOURCE(IDD_MENU), NULL, (DLGPROC)DlgMain);

break; // � um case, precisa de break;
                 }

///<---------------------------------------------------------------------------------------------------->

/// BOT�O DE INFORMA��ES | BT_INFO |

case BT_INFO: {        // CASO SEJA PRESSIONADO

EndDialog(hwndDlg, 0); // FECHA O DIAL�GO ATUAL, E NA LINHA ABAIXO CHAMA O DIAL�GO DIALOG_INFO

changeDialogSound(); /// beep decorativo

return DialogBoxA(hInst, MAKEINTRESOURCE(DIALOG_INFO), NULL, (DLGPROC)DlgMain);

break; // � um case, precisa de break;
              }

///<---------------------------------------------------------------------------------------------------->

/// BOT�O QUE V�LIDA O ACESSO AO PAINEL DE ADMNISTRA��O | BTN_ACESS |

case BTN_ACESS: {      // CASO SEJA PRESSIONADO

changeDialogSound();

char acessCode[10] = "202200132"; /// DEFINE O C�DIGO DE ACESSO PARA FAZER A COMPARA��O
char acessCodeValidation[10];     /// ENTRADA DO USU�RIO

/// AQUI O C�DIGO RECEBE O QUE FOI ESCRITO NA CAIXA DE TEXTO
GetDlgItemText(hwndDlg, QUAL_SENHA, acessCodeValidation, sizeof(acessCodeValidation));

/// AQUI OCORRE A COMPARA��O ENTRE AS 2 STRINGS PARA VER SE O USU�RIO ESCREVEU CERTO
if (strcmp(acessCodeValidation, acessCode) != 0){ // nesse caso n�o escreveu certo
    // Caixa de mensagens padr�o do windows (nesse caso avisa que o c�digo est� errado)
    MessageBox(hwndDlg, "Insira o c�digo de acesso correto!\n", "Allen", MB_ICONINFORMATION);
                                                }

/// AQUI PERMITE O ACESSO POR QUE NA COMPARA��O AS DUAS STRINGS S�O IGUA�S
else                                            {

EndDialog(hwndDlg, 0);  // Fecha o dial�go, e chama o pa�nel de controle "DIALOG_CONTROLE"
return DialogBoxA(hInst, MAKEINTRESOURCE(DIALOG_CONTROLE), NULL, (DLGPROC)DlgMain);
                                                }
break; // � um case, precisa de break;
                }

///<---------------------------------------------------------------------------------------------------->

/// BOT�O PARA ENTRAR NO LOGIN DE ADMIN | BTN_QUEUE_CREATE |

case BTN_QUEUE_CREATE: { // CASO SEJA PRESSIONADO

EndDialog(hwndDlg, 0); // Fecha o dial�go, e chama o login, "DIALOG_SENHA"

changeDialogSound(); /// beep decorativo

return DialogBoxA(hInst, MAKEINTRESOURCE(DIALOG_SENHA), NULL, (DLGPROC)DlgMain);

break; // � um case, precisa de break;
                       }

///<---------------------------------------------------------------------------------------------------->

/// BOT�O PARA ENTRAR DIRETAMENTE NA FILA | BTN_QUEUE |

case BTN_QUEUE: { // CASO SEJA PRESSIONADO

    changeDialogSound();

if (isCreatedQueue == 1) { // se existir uma fila

EndDialog(hwndDlg, 0); // Fecha o dial�go, e permite entrar na fila, "DIALOG_SEUNOME"

return DialogBoxA(hInst, MAKEINTRESOURCE(DIALOG_SEUNOME), NULL, (DLGPROC)DlgMain);

                         }

if (isCreatedQueue != 1) { //se n�o existir uma fila
                        // mostra uma messagebox, dizendo que n�o existe uma fila
MessageBox(hwndDlg, "No momento n�o existe nenhuma fila cadastrada! \nContate a adminisra��o para mais informa��es!\n", "Allen", MB_ICONINFORMATION);

                         }
break; // � um case, precisa de break;
                }

///<---------------------------------------------------------------------------------------------------->

/// BOT�O PARA CHECAR SE A FILA EXISTE | BTN_QUEUE_EXISTS |
/// bot�o para caso ocorra algum erro na valida��o da fila

case BTN_QUEUE_EXISTS: { // Caso pressionado

    changeDialogSound(); /// beep decorativo

fila = fopen("fila.txt", "r"); // L� O ARQUIVO FILA.TXT

if (fila) {         /// CASO LEIA
isCreatedQueue = 1; // diz que a fila existe
MessageBox(hwndDlg, "J� existe uma fila cadastrada no sistema!\n", "Allen", MB_ICONINFORMATION);
fclose(fila);
          }

else {              /// CASO N�O LEIA
                    // diz que a fila n�o existe
isCreatedQueue = 0;
MessageBox(hwndDlg, "N�o existe nenhuma fila cadastrada!\n", "Allen", MB_ICONSTOP);
     }
break; // � um case, precisa de break;
                       }

///<---------------------------------------------------------------------------------------------------->

/// BOT�O PARA CRIAR UMA FILA
case BTN_QUEUE_MAKE: { // CASO SEJA PRESSIONADO

changeDialogSound(); /// beep decorativo

if (isCreatedQueue == 1) { // CASO EXISTA UMA FILA N�O PODE SOBREESCREVER
MessageBox(hwndDlg, "J� existe uma fila! Delete a atual se realmente deseja criar uma nova!", "Allen", MB_ICONINFORMATION);
                         }

if (isCreatedQueue != 1) { // CASO N�O EXISTA CRIA UMA FILA

fila = fopen("fila.txt", "w"); /// CRIA O ARQUIVO

if (fila == NULL) {            /// SE OCORRER UM ERRO (RARAMENTE OCORRE)

printf("\n \nErro ao Criar a Fila!");
MessageBox(hwndDlg, "Erro ao Criar a Fila! Reinicie o Programa!\n", "Allen", MB_ICONERROR);

                  }
else {                        /// SE N�O ACONTECER NENHUM ERRO
isCreatedQueue = 1;                 // Diz que j� existe uma fila
fprintf(fila,"   > FILA ATUAL \n\n");  // Escreve no arquivo, e abaixo mostra uma messagebox dizendo que deu certo
MessageBox(hwndDlg, "Fila Criada com sucesso!\n", "Allen", MB_ICONINFORMATION);
     }
fclose(fila);  //Aqui fecha o arquivo
                          }
break; // � um case, precisa de break;
                      }

///<---------------------------------------------------------------------------------------------------->

/// Bot�o que chama uma confirma��o para apagar a fila.
case BTN_QUEUE_DELETE: { // CASO SEJA PRESSIONADO

changeDialogSound(); /// beep decorativo

if (isCreatedQueue == 1) { /// SE A FILA EXISTIR

/// Chama um dialogo "DIALOG_QUIERES_APAGAR", para confirmar se realmente quer apagar!
return DialogBoxA(hInst, MAKEINTRESOURCE(DIALOG_QUIERES_APAGAR), NULL, (DLGPROC)DlgMain);

                         }

if (isCreatedQueue != 1) { /// SE A FILA N�O EXISTIR

/// N�o tem como apagar algo que n�o existe, por isso chama uma mssgbox avisando isso!
MessageBox(hwndDlg, "N�o existe uma fila para ser apagada!\n", "Allen", MB_ICONINFORMATION);
                         }
break; // � um case, precisa de break;

                       }

/// DIALOGO REFERENTE A CONFIRMA��O -> "CHILD" OF BTN_QUEUE_DELETE

                        /// Bot�o de Cancelar!
                        case COMP_CANCEL: { // Caso pressionado!

                    // como � uma popup ele fecha o dialogo de confirma��o e volta pro controle
                        EndDialog(hwndDlg, 0);
                        changeDialogSound(); /// beep decorativo

                        break; // � um case, precisa de break;
                                          }

                        /// Bot�o de Confirmar!
                        case COMP_AFFIRM: { // Caso pressionado!

                     // como � uma popup ele fecha o dialogo de confirma��o e volta pro controle
                        EndDialog(hwndDlg, 0);
                        changeDialogSound(); /// beep decorativo
                            remove("fila.txt"); //apaga o arquivo
                            system("cls");
                        isCreatedQueue = 0;     // afirma que n�o existe nenhuma fila
                        MessageBox(hwndDlg, "A fila foi removida!\n", "Allen", MB_ICONSTOP); // mostra confirma��o que apagou

                        break; // � um case, precisa de break;
                                          }

///<---------------------------------------------------------------------------------------------------->

/// Bot�o de confirma��o de nome

case BTN_CONFIRM_TICK: { // caso apertado

    changeDialogSound(); /// beep decorativo

// string que ir� armazenar temporariamente o nome da pessoa
char nomeOfThePeople[1024*8];

/// sistema recebe o valor da caixa de texto / "label", e armazena em "nomOfThePeople"
GetDlgItemText(hwndDlg, ENTRADA_NOME_ARMAZENAR, nomeOfThePeople, sizeof(nomeOfThePeople));

fila = fopen("fila.txt", "a"); // abre o arquivo e adiciona o nome

if (fila == NULL) // se der erro
   {
MessageBox(hwndDlg, "Ocorreu um Erro com a fila contate a administra��o poss�velmente a mesma foi apagada!\n", "Allen", MB_ICONASTERISK);
   }

else {       // dando certo

/// Em resumo: ser� printado o nome da pessoa na fila sem apagar quem j� tinha escrito
fprintf(fila,"   # %s\n", nomeOfThePeople);
fclose(fila); // fecha o arquivo
EndDialog(hwndDlg, 0);
return DialogBoxA(hInst, MAKEINTRESOURCE(IDD_MENU), NULL, (DLGPROC)DlgMain);

     }

break; // � um case, precisa de break;
                      }

///<---------------------------------------------------------------------------------------------------->

/// Bot�o para printar / mostrar o conte�do da fila
case BTN_CHECK_THE_QUEUEPEOPLE: {

    changeDialogSound(); /// beep decorativo

if (isCreatedQueue == 1) { // Se existe uma fila

/// exibe uma mensagem avisando que a fila foi gerada, e dps imprime a fila no console
MessageBox(hwndDlg, "A lista para voc� checar foi gerada! D� uma olhada no console.\n", "Allen", MB_OK);
system("cls");

fila = fopen("fila.txt", "r"); // aqui l� o conte�do do arquivo

while (fgets(lista_formatada, 100000000, fila) != NULL) // organiza conte�do para impress�o
printf("%s", lista_formatada); // printa a fila

fclose(fila); // fecha a lista

                         }
if (isCreatedQueue != 1) { // caso n�o exista lista n�o mostrar� nada
MessageBox(hwndDlg, "O sistema n�o cadastrou nenhuma fila!\n", "Allen", MB_ICONASTERISK);
                         }
break; // � um case, precisa de break;
                                }

///<---------------------------------------------------------------------------------------------------->

}/// FIM DA DECLARA��O DE COMANDOS

} return TRUE; /// PRECISA DAR CERTO
} return FALSE;/// SE DER ERRO S� SAI DO SWITCH
}


/// AQUI FUNCIONA DA MESMA FORMA QUE O "int main()", NO CASO CHAMANDO A FUN��O BOOL ACIMA
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){

/// FUN��ES DE INICIALIZA��O PADR�O DE UM C�DIGO EM LINGUAGEM C

                                                /// EM RESUMO
    setlocale (LC_ALL, "Portuguese-Brazilian"); /// DEFINE A LOCALIZA��O DO C�DIGO
             // A IDE utilizada n�o aceita " ", que aceita todo e qualquer caractere existente
    SetConsoleTitle("[C] - Vostoorganizanto 2.0 - Made by allen");  /// DEFINE O T�TULO DO CONSOLE
    system("COLOR E0");                         /// DEFINE A COR DE FUNDO DO CONSOLE

/// AQUI OS CONTROLES DE DIALOGOS, BOT�ES, LABELS, S�O CHAMADOS / EXECUTADOS;
    hInst = hInstance;
    InitCommonControls ();



/// TESTE PARA SABER SE J� EXISTE UMA FILA E CASO EXISTA A ESCOLHA
    if (isCreatedQueue == 0){ fila = fopen("fila.txt", "r");
                              if (fila) { isCreatedQueue = 1; fclose(fila); }
                              else      { isCreatedQueue = 0;               }
                            }

changeDialogTest();

/// AQUI CHAMAMOS O PRIMEIRO DIAL�GO
    return DialogBoxA(hInst, MAKEINTRESOURCE(IDD_MENU), NULL, (DLGPROC)DlgMain);
                                                                                               }




