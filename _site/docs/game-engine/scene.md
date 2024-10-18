# SCENE.LST

#rem
#rem Liste HQR des fichiers nécéssaires au fonctionnement
#rem de TimeCommando PC
#rem
#rem OBJETS et ARMES de la scène
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.SCC
#rem FICHES des OBJETS et des ARMES
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.FIC
#rem PROGRAMMES (tracks) des OBJETS
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.TRK
#rem BODIES des OBJETS et ARMES
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.BOC
#rem SAMPLES
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.SAC
#rem ANIMATIONS des OBJETS
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.ANC
#rem TEXTURES des OBJETS et ARMES
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.TEX
#rem FEUILLES 3D du sol
F:\PROJET\TIME\GRAPH\DECORS\STAGE00\RUN0\SCENE.SOL
#rem Palette SHADE
F:\PROJET\TIME\GRAPH\DECORS\STAGE00\RUN0\PALTIME.SHD
#rem SPRITES 320x240
F:\PROJET\TIME\GRAPH\SPRITES\STAGE00\ICO240.GPH
#rem SPRITES 320x480
F:\PROJET\TIME\GRAPH\SPRITES\STAGE00\ICO480.GPH
#rem SPRITES 640x480
F:\PROJET\TIME\GRAPH\SPRITES\STAGE00\ICO640.GPH
#rem définition des QUAD
F:\PROJET\TIME\SCENE\STAGE00\RUN0\SCENE.QAD
#rem définition des ZONES, COLLISIONS, BONUS, FLOTS et EFFETS
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.BNC
#rem définition des SPRITES 3D
F:\PROJET\TIME\GRAPH\SPRITES\STAGE00\EFFETS.GPR
#rem définition des MUSIQUE OPL
F:\PROJET\TIME\MUSIC\STAGE00\MUSIC_OP.XMI
#rem définition des MUSIQUE GENERAL MIDI
F:\PROJET\TIME\MUSIC\STAGE00\MUSIC_GM.XMI



#rem
#rem Liste HQR des fichiers nécéssaires au fonctionnement
#rem de TimeCommando PSX
#rem
#rem SAMPLES
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.SAX
#rem Music Midi Track
F:\PROJET\TIME\MUSIC\STAGE00\PSX\TC300_PS.SNG
#rem Music SAMPLES
F:\PROJET\TIME\MUSIC\STAGE00\PSX\TC300_PS.SNV
#rem TEXTURES des OBJETS et ARMES
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.TEX
#rem Texte démarrage en 16 couleurs (4bits)
F:\PROJET\TIME\PSX\RESS\TEXTS0.DAT
#rem SPRITES 640x240
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.SPR
#rem PROGRAMMES (tracks) des OBJETS
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.TRK
#rem BODIES des OBJETS et ARMES
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.BOX
#rem ANIMATIONS des OBJETS
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.ANX
#rem FICHES des OBJETS et des ARMES
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.FIX
#rem FEUILLES 3D du sol
F:\PROJET\TIME\GRAPH\DECORS\STAGE00\RUN0\SCENE.SOL
#rem définition des QUAD
F:\PROJET\TIME\SCENE\STAGE00\RUN0\SCENE.QAD
#rem définition des ZONES, COLLISIONS, BONUS, FLOTS et EFFETS
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.BNX
#rem OBJETS et ARMES de la scène
F:\PROJET\TIME\SCENE\STAGE00\RUN0\TEMP\SCENE.SCC







ViewHqr V1.11 (c)Adeline Software by Seb (Jan 14 1997 / 15:11:34)

File ..\SCENE.HQR - Size: 1001450 - Entries: 17
--------------------------------------------------------------------

Num   Name          Offset     Size       SizeComp    Method 
----  ------------  ---------  ---------  ---------   -------
   0  SCENE.SCC            74       1124        539   LZMIT
   1  SCENE.FIC           626       8864       3813   LZMIT
   2  SCENE.TRK          4450       5039       2952   LZMIT
   3  SCENE.BOC          7414     257580     144617   LZMIT
   4  SCENE.SAC        152042     919600     699052   LZMIT
   5  SCENE.ANC        851106     241360      75052   LZMIT
   6  SCENE.TEX        926170     106496      40654   LZMIT
   7  SCENE.SOL        966834       8476       3743   LZMIT
   8  PALTIME.SHD      970590       4096       1898   LZMIT
   9  ICO240.GPH       972498       3095       2972   LZMIT
  10  ICO480.GPH       975482       5954       5408   LZMIT
  11  ICO640.GPH       980902       9920       8802   LZMIT
  12  SCENE.QAD        989714       4400       2377   LZMIT
  13  SCENE.BNC        992102       1392       1026   LZMIT
  14  EFFETS.GPR       993138       1669        381   LZMIT
  15  MUSIC_OP.XMI     993530       5698       3797   LZMIT
  16  MUSIC_GM.XMI     997338       5820       4100   LZMIT
--------------------------------------------------------------------
Total:                           1590583    1001183   37.06%
--------------------------------------------------------------------



# SCENE.SCE

SetObj [Object Name] [Class name]
  InitPosition [X] [Y] [Z]
  InitLifeFrame [Start] [End] [Lock]
  InitBeta [Angle]
  InitBody [3D Object]
  InitAnim [Animation]
  InitLifePoint [Hit points]
  InitWeapon [Weapon name] [Ammonition count]
  Init...

  StartProgram
   (main script)
  EndProgram

  StartProgram
   (one or many subroutines)
  EndProgram
EndObj

SetTrack
  StartProgram
   (main script)
  EndProgram
EndTrack

SetWeapon Stone
  InitPosition    6450,-1,2650
  InitLifeFrame   -1, 175
  InitBeta        0
  Count           1
EndWeapon






# SCENE.SCC

#define OBJECT_NO_FLAG        0
#define OBJECT_TARGET         1
#define OBJECT_SHADOW         2
#define OBJECT_ZV             4
#define OBJECT_IMMORTEL       8
#define OBJECT_GRAVITY       16
#define OBJECT_INSHOCKABLE   32
#define OBJECT_GIVE_WEAPON   64
#define OBJECT_FLYING       128
#define OBJECT_HERO_RUN     256


SCENE:
    U8  count_object
    U8  count_weapon
    U8  count_weapon_description
    U8  count_track

    U8  count__bonus_hide
    U8  count_chip
    U8  base_sprite_2d     // PSX Only
    U8  base_sprite_3d     // PSX Only

    S16 num_stage 
    S16 num_run

OBJECT
    S32     x
    S32     y
    S32     z

    U16     beta

    S16     start_frame
    S16     end_frame    
    S16     lock_frame

    U16     offset_description
    U16     offset_track

    WEAPON_INVENTORY weapons[6]

    U16     flag
    U8      num_body
    U8      num_anim
    U8      lifepoint
    U8      nb_slot
    U8      type_give_bonus
    U8      nb_give_bonus

WEAPON_INVENTORY
    U8      nb2
    U8      pad
    U8      nb
    U8      num




TRACK
    U16     start_frame
    U16     end_frame

    U16     offset_track
    U8      pad[2]

WEAPON
    S32     x
    S32     y
    S32     z

    U16     beta
    U16     start_frame

    U16     end_frame
    U16     offset_description

    U8      nb_arme
    U8      num_arme
    U8      pad[2]




## Sample Script

SetObj Dragon   dragon
  InitPosition    51000, -1, 4650
  InitBeta        3072
  InitLifePoint   40,4
  InitLifeFrame   882, -1, 922
  InitBody        Dragon
  InitAnim        dra_Rien
  InitArme        BouleDeFeu 8
  InitArme        Crache 199
  InitFlagNoGiveWeapon
  StartProgram
    Loop
      UnFollow
      FollowHero
      DoAnimRepeat dra_Marche
      ExitProgram

      While TestAlive(Hero)
        // pour tester plusieurs fois cette distance
        __dho = GetDistance(Hero)

        If __jouefurie
          If TestAnim(dra_ChocF) | TestAnim(dra_ChocD) | TestAnim(dra_ChocG)
            WaitAnim
          EndIf
          Fury(dra_CoupBoule)
          WaitAnim
          __jouefurie = 0
        Else
            // pour furie
            If TestTouched
              If GetSameHit > 2
                __jouefurie = 1
                ExitProgram
              Else
                // temps d'attente en fct de difficulty
                If _dif==0
                  DoAnimOnce GetValueListRandom(dra_garde, dra_garde, dra_garde, 
                                                dra_garde, dra_rien)
                ElseIf _dif==1
                  DoAnimOnce GetValueListRandom(dra_tourD, dra_tourG, dra_garde)
                ElseIf _dif==2
                  DoAnimOnce GetValueList(-1, dra_tourD, dra_tourG)
                EndIf
                WaitAnim
              EndIf
              ClearTouched
            ElseIf TestBlocked | !TestTrajectoire3D(Hero) | (!GetRandom(200) & 
                                                     GetDistance(Hero < 3000))
              //DoAnimOnce GetValueList(-1, dra_tourd, dra_tourG)
              DoAnimOnce GetValueList(-1, dra_Marched, dra_MarcheG)
              WaitAnim

              UnFollow
              FollowPoint 47881, 6406
              ClearTouched
              ExitProgram
              Wait GetDistancePoint(47881, 6404) < 1000 | TestTouched
              UnFollow
              FollowHero
              ExitProgram
            EndIf

            // Comportement selon distance  Hero/Objet
            If __dho < 475
              // trop pres => recule ou coup de boule
              If (TestLance | TestFrappe)
                If _dif==0
                  DoAnimOnce GetValueList(-1, dra_Esqf, dra_Garde)
                Else
                  DoAnimOnce dra_CoupBoule
                EndIf
              Else
                DoAnimOnce GetValueListRandom(dra_Esqf, dra_MarcheD, dra_MarcheG, 
                      dra_CoupBoule, dra_CoupBoule, dra_CoupBoule, dra_CoupBoule)
              EndIf
            ElseIf __dho < 1480-400
              If (TestLance | TestFrappe)
                GoSub Defense
              Else
                DoAnimOnce GetValueListRandom(dra_CoupBoule, dra_CoupBoule, 
                                dra_CoupQueue, dra_crache50cmFlot, dra_CoupBoule)
                GoSub SiEsquive
              EndIf
              ExitProgram
            ElseIf __dho < 1555-400
              If (TestLance | TestFrappe)  & !GetRandom(_dif)
                GoSub Defense
              Else
                DoAnimOnce GetValueListRandom(dra_CoupBoule, dra_CoupBoule, 
                            dra_CoupQueue, dra_crache50cmFlot, dra_crache50cmFlot, 
                            dra_Crache50cmFlot, dra_CoupBoule)
                GoSub SiEsquive
              EndIf
              ExitProgram
            ElseIf __dho < 2740-400
              If (TestLance | TestFrappe)  & !GetRandom(_dif)
                GoSub Defense
              Else
                DoAnimOnce GetValueListRandom(dra_crache50cmFlot, 
                          dra_crache50cmFlot, dra_crache50cmFlot, dra_CoupQueue)
                GoSub SiEsquive
              EndIf
              ExitProgram
            ElseIf __dho < 2815-400
              If (TestLance | TestFrappe)  & !GetRandom(_dif)
                GoSub Defense
              Else
                DoAnimOnce GetValueList(-1, dra_crache50cmFlot, 
                           dra_crache50cmFlot, dra_crache50cmFlot, dra_CoupQueue)
                GoSub SiEsquive
              EndIf
              ExitProgram
            ElseIf __dho < 3115-400
              If (TestLance | TestFrappe)  & !GetRandom(_dif)
                GoSub Defense
              Else
                DoAnimOnce GetValueList(-1, dra_CoupQueue, dra_Crache50cmFlot)
                GoSub SiEsquive
              EndIf
              ExitProgram
            ElseIf GetNBArme(BouleDeFeu)<>0
              // trop loin => avance ou crache
              If _dif==0
                If OtherGetYPos(Hero) > GetYPos
                  DoAnimOnce GetValueListRandom(dra_rien, dra_garde, dra_garde, 
                                      dra_crache100cm, dra_marche, dra_marcheD, 
                                      dra_marcheG, dra_Crache100cm)
                Else
                  DoAnimOnce GetValueListRandom(dra_rien, dra_garde, 
                                      dra_crache100cm, dra_marche, dra_marcheD, 
                                      dra_marcheG, dra_Crache100cm)
                EndIf
              ElseIf _dif==1
                If OtherGetYPos(Hero) > GetYPos
                  DoAnimOnce GetValueListRandom(dra_rien, dra_garde, 
                                      dra_crache100cm, dra_marcheD, dra_marcheG, 
                                      dra_Crache100cm)
                Else
                  DoAnimOnce GetValueListRandom(dra_rien, dra_garde, 
                                      dra_crache50cm, dra_marcheD, dra_marcheG, 
                                      dra_Crache50cm)
                EndIf
              ElseIf _dif==2
                If OtherGetYPos(Hero) > GetYPos
                  DoAnimOnce GetValueListRandom(dra_garde, dra_crache100cm, 
                                      dra_marcheD, dra_marcheG, dra_Crache100cm)
                Else
                  DoAnimOnce GetValueListRandom(dra_garde, dra_crache50cm, 
                                      dra_marcheD, dra_marcheG, dra_Crache50cm)
                EndIf
              Else
                If OtherGetYPos(Hero) > GetYPos
                  DoAnimOnce GetValueListRandom(dra_crache100cm, dra_marcheD, 
                                      dra_marcheG, dra_Crache100cm)
                Else
                  DoAnimOnce GetValueListRandom(dra_crache50cm, dra_marcheD, 
                                      dra_marcheG, dra_Crache50cm)
                EndIf
              EndIf
              ExitProgram
            EndIf
        EndIf
        ExitProgram
      EndWhile

      UnFollow

      DoAnimRepeat dra_Rien

      While !TestAlive(Hero)
        ExitProgram
      EndWhile
      ExitProgram
    EndLoop
  EndProgram

  StartProgram SiEsquive
    WaitAnim
    If !OtherTestTouched(Hero)
      // si on l'a rate 2 fois d'affilee : peut etre un pb d'angle
      __rate = __rate+1
      If __rate == 2
        Gosub Defense
        __rate = 0
      EndIf
    Else
      Gosub Defense
      OtherClearTouched(Hero)
      WaitAnim
    EndIf
  EndProgram

  StartProgram Defense
    If _dif==0
      DoAnimOnce GetValueListRandom(dra_Garde, dra_Garde, dra_Rien, dra_marche)
    ElseIf _dif==1
      DoAnimOnce GetValueListRandom( dra_Esqf, dra_MarcheD, dra_MarcheG)
    ElseIf _dif==2
      DoAnimOnce GetValueListRandom( dra_Esqf, dra_MarcheD, dra_MarcheG)
    Else
      DoAnimOnce GetValueListRandom( dra_Esqf, dra_MarcheD, dra_MarcheG)
    EndIf
  EndProgram

EndObj
