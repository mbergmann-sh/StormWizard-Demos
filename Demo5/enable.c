/*
/       Programm: ASLrequest (Wizard-Demo 5)
/       Datei:  enable.c
/       Version: 1.0
/       Compiler: StormC3/StormGCC4/SAS C, GNU gcc
/       Oberfl�che erstellt mit StormWizard v2.3
/       (�berarbeitete Version von Bernd Roesch)
/
/       Aufgaben:       Demo zur Verwendung der wizard.library unter StormC3, StormGCC4,
/                                       SAS C v6.58 und Geek Gadgets gcc v2.95
/       Trivia:         Das Programm illustriert die Manipulation von Gadgets zur Laufzeit
/
/       Autor: Michael Bergmann, mbergmann-sh@gmx.de
/
/       Hinweise: GNU gcc ohne Overload - noixemul (-noixemul), libnix (-lnix), math (-lm)
/       Aufruf GNU gcc v2.95: gcc -pedantic -Wall -noixemul -lnix -lm -O2 <quelldatei.c> -o <programmname_gcc>
/       Aufruf SAS C v6.58: sc ERRORREXX CPU=68x00 <quelldatei.c> link to <programmname_sas>
*/

/* zu ladendes GUI */
char *GUI = "enable.wizard";

/* Versionsstring: */
char *ver = "\0$VER: enable  v1.0.0 (28. September 2012) � Michael Bergmann";

/* Einbinden der ben�tigten System-Headerdateien        */
#include "mbHeaders.h"

/* Macrodefinitionen zur Schnittstelle (StormWizard-generiert) */
#include "enable.h"

/* Makros, die das Leben leichter machen... */
#define setDisableGadget(gad, win) SetGadgetAttrs((gad),(win),NULL,GA_Disabled,TRUE, TAG_DONE)
#define setEnableGadget(gad, win) SetGadgetAttrs((gad),(win),NULL,GA_Disabled,FALSE, TAG_DONE)

/* Prototypen f�r eigene Funktionen: */


/* StormC3 und SAS/C �ffnen und schlie�en bestimmte Systembibliotheken b. B. selbstst�ndig */
/* F�r andere Compiler gilt: Bibliotheken "von Hand" �ffnen und schlie�en! */
int init_libraries( void);
void exit_libraries( void);


/* hier Basiszeiger f�r verwendete Bibliotheken eintragen */
struct IntuitionBase *IntuitionBase;
#ifdef __SASC
struct Library *UtilitiyBase;
#else
struct UtilityBase *UtilityBase;
#endif
struct Library *AslBase;
struct Library *WizardBase;

APTR   surface;
struct Screen   *screen;
struct NewWindow *newwin;
struct Window   *window;                        // Bezeichner gem�� Angaben in StormWizard f�r eigene Programme anpassen!
struct WizardWindowHandle *winhandle;
struct Gadget *gads[WINDOW_MAIN_GADGETS];       // Index gem�� Angaben in StormWizard f�r eigene Programme anpassen!
struct IntuiMessage *msg;


/* Struktur f�r EasyReQuest */
#define NO 0
#define YES 1
/* Easy Requester Frage */
   struct EasyStruct myreq = {
     sizeof(struct EasyStruct),
     0,
     "Button disabled/enabled",
     "Der Zustand des Gadgets wurde ver�ndert.",
     "Ach, wie sch�n!|Mir doch egal..."
   };

/*
 *	main()
 */
int main( void)
{
	BOOL Flag;
	long result;                            // R�ckgabewert des EasyRequesters
	long wert;										 // R�ckgaewert des Toggle-Gadgets

	/* Systembibliotheken �ffnen (nicht f�r die alte Version 3 von StormC!) */
	if(! init_libraries( ))                 // ben�tigt, falls nicht mit StormC compiliert
		return 0;                            // Fehler werfen!

	// Erstmal die Oberfl�chenbeschreibung bereitstellen!
	if ((surface=WZ_OpenSurface(GUI, 0L, TAG_DONE)))
	{
		// Nat�rlich brauchen wir auch einen Screen oder?
		if ((screen=LockPubScreen(0L)))
		{

			// Jetzt holen wir uns ein WindowHandle, mit dem unsere Objekte
			// durch die wizard.library verwaltet werden.
			if ((winhandle=WZ_AllocWindowHandle(screen,0L, surface,TAG_DONE)))
			{

				// Da ein WindowHandle nur Sinn macht, wenn auch die Objekte
				// darin vorkommen, legen wir diese Objekte jetzt an.
				if ((newwin=WZ_CreateWindowObj(winhandle,WINDOW_MAIN,WWH_GadgetArray,(int)gads,
																							WWH_GadgetArraySize,(int)sizeof(gads),
																							TAG_DONE)))
				{

					// Nachdem das glatt ging, versuchen wir unser
					// Fenster zu �ffnen. Dabei werden alle Objekte installiert.
					if ((window=WZ_OpenWindow(winhandle,newwin,WA_AutoAdjust,TRUE,
																			TAG_DONE)))
					{
						Flag=TRUE;   // Flag zum Beenden der nachfolgenden Schleife
										// TRUE: Schleife l�uft weiter
									  // FALSE: Schleife wird beendet

						do      // durchlaufe die Schleife solange, bis Abbruchbedingung (Flag = FALSE) erf�llt ist
						{
							// Da wir keine Rechenzeit verschwenden wollen, werden wir
							// das Program "schlafen" legen, bis eine Nachricht
							// eintifft. F�r Profis gilt, das auch Wait() verwendet
							// werden kann.
							WaitPort(window->UserPort);

							if ((msg=(struct IntuiMessage *)GetMsg(window->UserPort)))      // Message abholen
							{
								switch(msg->Class)                      // IDCMP-Flags unterscheiden:
								{
									case IDCMP_CLOSEWINDOW: // CloseWindow gedr�ckt ?
										{
											Flag = FALSE;
										}
										break;

									/* Kam die Message von einem Gadget?                                           */
									/* (Symbolische Konstanten der Gadgets gem�� Angaben in StormWizard anpassen!) */
									case IDCMP_IDCMPUPDATE:
									{
										switch(GetTagData(GA_ID,0,(struct TagItem *)msg->IAddress))     // Aufrufer unterscheiden
											{
												/* GADGETS */
												case BT_EINS:
												{
													SetGadgetAttrs(gads[BT_ZWEI], window, NULL,GA_Disabled, FALSE, TAG_END);
													SetGadgetAttrs(gads[BT_EINS], window, NULL,GA_Disabled, TRUE, TAG_END);
													WZ_LockWindow(winhandle);
													result = EasyRequest(window, &myreq, NULL, NULL);
													WZ_UnlockWindow(winhandle);
												}
												break;
												case BT_ZWEI:
												{
													/*
													* SetGadgetAttrs(gads[BT_EINS], window, NULL,GA_Disabled, FALSE, TAG_END);
													* SetGadgetAttrs(gads[BT_ZWEI], window, NULL,GA_Disabled, TRUE, TAG_END);
													*
													*	Klappt auch sehr sch�n mit Macros:
													*/
													setEnableGadget(gads[BT_EINS], window);
													setDisableGadget(gads[BT_ZWEI], window);
													WZ_LockWindow(winhandle);
													result = EasyRequest(window, &myreq, NULL, NULL);
													WZ_UnlockWindow(winhandle);
												}
												break;
												case TG_SLIDE:
												{
													gettoggle(gads[TG_SLIDE], &wert);
													switch(wert)
													{
														case 0:
															setDisableGadget(gads[HSL_ZAHL], window);
															setDisableGadget(gads[IG_ZAHL], window);
														break;
														case 1:
															setEnableGadget(gads[HSL_ZAHL], window);
															setEnableGadget(gads[IG_ZAHL], window);
															// SetGadgetAttrs(gads[TG_SLIDE], window, NULL,WGA_Label, "Disable", TAG_END);
														break;
													}
												}
												break;

											}
									}
									break;

									/* Kam die Message von einem Men�?                                           */
									/* (Symbolische Konstanten der Men�s gem�� Angaben in StormWizard anpassen!) */
									case IDCMP_MENUPICK:
									switch(msg->Code)               // Welcher Eintrag wurde gew�hlt?
									{
										;
									}

								}

								// Da wir keine Speicherleichen dulden und
								// das Nachrichtensystem nicht durcheinanden bringen
								// wollen, teilen wir den Betriebssystem mit, das
								// die Nachricht von uns nicht mehr ben�tigt wird.
								ReplyMsg((struct Message *)msg);
							}
						}
						while (Flag);   // ...solange Flag == TRUE: Schleife fortsetzen!

						// Fenster schlie�en
						WZ_CloseWindow(winhandle);
					}
				}

				// In jedem Fall mu� ein mit WZ_AllocWindowHandle() angelegter
				// WindowHandle auch wieder freigegeben werden. �brigens
				// kann das Fenster hierbei noch offen sein. Probieren Sie es!
				WZ_FreeWindowHandle(winhandle);
			}

			// PublicScreen-Benutzerz�hler wieder um eins verringern
			UnlockPubScreen(0L,screen);
		}
		/* Fensterposition f�r n�chsten Start merken*/
		WZ_SnapShot(surface,TAG_DONE);

		// Da wir keine Objekte von dieser Surface mehr besitzen und wir diese
		// auch nicht mehr anlegen geben wir sie frei. �brigens noch
		// nicht freigegebene WindowHandles werden hierbei von der
		// wizard.libarry entfernt (Fenster auch geschlossen).
		WZ_CloseSurface(surface);
	}

		/* Systembibliotheken schlie�en (nicht unter StormC!) */
			exit_libraries();

}       // main() ENDE


/*
 * Funktion: init_libraries()
 * �ffnen von Systembibliotheken
 */
int init_libraries( void)
{
	/*  nicht zwingend ben�tigt, wenn gcc mit -lauto aufgerufen wird */
	if(! (IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library",37L)))
	{
		printf("intuition.library konnte nicht ge�ffnet werden!\n");
		return 0;
	}
	#ifdef __SASC
	if(! (UtilityBase = (struct Library *)OpenLibrary("utility.library",37L)))
	#else
	if(! (UtilityBase = (struct UtilityBase *)OpenLibrary("utility.library",37L)))
	#endif
	{
		printf("utility.library konnte nicht ge�ffnet werden!\n");
		return 0;
	}
	if(! (AslBase = (struct Library *)OpenLibrary("asl.library",37L)))
	{
		printf("asl.library konnte nicht ge�ffnet werden!\n");
		return 0;
	}

	if(! (WizardBase = (struct Library *)OpenLibrary("wizard.library",37L)))
	{
		printf("wizard.library konnte nicht ge�ffnet werden!\n");
		return 0;
	}
	return 1;
}


/*
 * Funktion: exit_libraries()
 * Schlie�en von Systembibliotheken
 */

void exit_libraries( void)
{
	if ( IntuitionBase )
		CloseLibrary((struct Library *) IntuitionBase);
	if ( UtilityBase )
		CloseLibrary((struct Library *) UtilityBase);
	if ( AslBase )
		CloseLibrary((struct Library *) AslBase);
	if ( WizardBase )
		CloseLibrary((struct Library *) WizardBase);
}


