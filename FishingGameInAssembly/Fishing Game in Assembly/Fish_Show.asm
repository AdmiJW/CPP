
TITLE Showing the Fish Catched by Level

INCLUDE Irvine32.inc

.data
	Lv0_Fail BYTE "You reel in, and see nothing on your hook. You are dissapointed", 13, 10, 13, 10
		BYTE "You gained $0 and 0 Experience.", 13, 10, 0
	Lv1_TinCan BYTE "                           ((((/////**                        ", 13, 10
		BYTE "                          #(#((((///////                      ", 13, 10
		BYTE "                           ,,###(((((///(/                    ", 13, 10
		BYTE "                           %%#%####((((((#(                   ", 13, 10
		BYTE "                             *(%%%#####(#((                   ", 13, 10
		BYTE "                               &((%%%%#(#/#                   ", 13, 10
		BYTE "                    #(**/((##%%%%%#((/%%((                    ", 13, 10
		BYTE "                    /#,  ./%%%%%%%%(.  .#/                    ", 13, 10
		BYTE "                    /*,.  ,*(####(/,. .,*/                    ", 13, 10
		BYTE "                    (*,...,*(##*#(/*,...*(                    ", 13, 10
		BYTE "                    //*   .,(#%%#(*,   ,//                    ", 13, 10
		BYTE "                    /*. ..,/(#####/*,. .*/                    ", 13, 10
		BYTE "                    (**.  .,/(##((*,  .,*/                    ", 13, 10
		BYTE "                    /*.  .*/(#%%##(/. ..//                    ", 13, 10
		BYTE "                    /*...,.,/(##((*,,...*/                    ", 13, 10
		BYTE "                    (**.  .*(#%%##/,  .,,(                    ", 13, 10
		BYTE "                    /*. .,*//(#((((/,. .*/                    ", 13, 10
		BYTE "                    /*,. .,*(####(/*...,*/                    ", 13, 10
		BYTE "                     / . .,*(####(/*... /                     ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 1] You caught a tin can! Ugh!", 13, 10
		BYTE "You gained $0 and 1 Experience", 13, 10, 0
	Lv2_Seaweed BYTE "                                        #(                    ", 13, 10
		BYTE "                               .       *#/*      ##           ", 13, 10
		BYTE "               .*              .#(,   ./%#,**,* *#(,          ", 13, 10
		BYTE "     %#.         ../,       ,#(*.%%(  (#(#,,*/*//%,#          ", 13, 10
		BYTE "       ,*#,          ../     .,,%###%**#%//  *(/###/          ", 13, 10
		BYTE "           (%##/          *.     .*.,,%##(%.//*.((/#/     .   ", 13, 10
		BYTE "            .#%%(*         . /     ( (%&%,/((* .//*/#.   /    ", 13, 10
		BYTE "              .,/%#(                ,%%%%#*/*,//,**(#%#(,     ", 13, 10
		BYTE "                   ,%/              /#%#%%(/   .,/((((*       ", 13, 10
		BYTE "                     .#            .((#(&%(     /*//(/        ", 13, 10
		BYTE "                       (*          ((#./%&*  (///(#((         ", 13, 10
		BYTE "                       ,%%(       %%#./(#%&%(*(*(#(/*         ", 13, 10
		BYTE "                        /((/      %%(.((/#%%. .#(/,,          ", 13, 10
		BYTE "                         ///     ,%#,(%%(#&% ###/,.           ", 13, 10
		BYTE "                          *##    #%#%&//%&%(##(/.             ", 13, 10
		BYTE "                           .*#   %%%%#%&&%%%#*                ", 13, 10
		BYTE "                             ,% *%%&&&&&%#%*                  ", 13, 10
		BYTE "                             .(#%&&&&%#%/                     ", 13, 10
		BYTE "                             *#%%&&%&#.                       ", 13, 10
		BYTE "                             %%&&%&#./.                       ", 13, 10
		BYTE "                           .%#%%&#.                           ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 2] You caught a seaweed! At least it is better than tin can perhaps?", 13, 10
		BYTE "You gained $0 and 3 Experience", 13, 10, 0
	Lv3_Boots BYTE "                   #%%(/#%@/#%(  #/                           ", 13, 10
		BYTE "                  /(%%%%%&&#(#&%%%*                           ", 13, 10
		BYTE "                  (#%#%#/(%&%%&#&/                            ", 13, 10
		BYTE "                   (%##((%%*%%&@(                             ", 13, 10
		BYTE "                  ,(%%(##%%#@##@                              ", 13, 10
		BYTE "                   #%%##/#%%&#%&                              ", 13, 10
		BYTE "                  #%&%#(#(#(&@##%                             ", 13, 10
		BYTE "                  ((##(%#(####(&@(                            ", 13, 10
		BYTE "                 (&/&%%%##%#####(##%                          ", 13, 10
		BYTE "                 #&##(%%&#%%#(#%##(#&%                        ", 13, 10
		BYTE "                /%%#####(%%%%%%#(##((#(/(                     ", 13, 10
		BYTE "                /###%##&#&#####%#(#%####(###((*               ", 13, 10
		BYTE "                   &%%%&*/%&#####%#%#(((##(**((               ", 13, 10
		BYTE "                            %#%%&@&&&&(###%//(%/              ", 13, 10
		BYTE "                                (####((/((,                   ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 3] You caught a used boot! It is quite heavy to say the least?", 13, 10
		BYTE "You gained $0 and 5 Experience", 13, 10, 0
	Lv4_Goldfish BYTE "      ..,                                                     ", 13, 10
		BYTE "      ....,,,                 .......,...                     ", 13, 10
		BYTE "      ...,,,*,/,           ....,,,,****/***(                  ", 13, 10
		BYTE "      ...,,,,,,***        **,,**///(//(///((((                ", 13, 10
		BYTE "      ...,,,,/,**(//     ,***/##%#%%%%%##%%%###*              ", 13, 10
		BYTE "      ....,,,*,*/*//(   **/###%%#####(###########             ", 13, 10
		BYTE "        ..,,,,/***((## */(#####(#(((((#(/((###%%#%%#          ", 13, 10
		BYTE "         .,,,,,/**(#%%%/###((((((/((//(////(((#####((##%      ", 13, 10
		BYTE "          ,,,,,***((%#((///(///*/(*//*////*///(#(#((((((##    ", 13, 10
		BYTE "           ,,,,**//(%%((/((///*//**/*****///*(/(#####(/(((#*  ", 13, 10
		BYTE "          ,,,,,***/(#%%.*(#(/////*****,****/*(/((((((((@%#((# ", 13, 10
		BYTE "         .,,,,,**///(# .*/(/(#(*//**********/(/(////////((((# ", 13, 10
		BYTE "        ..,,,,,***(((,  .,*(((((////**/**//*/(#//////////(((# ", 13, 10
		BYTE "      ....,*,,**/*//,         .,,,*///(*/((/(###(#**          ", 13, 10
		BYTE "      ....,,,,,**(/          .,*****//##/(((((                ", 13, 10
		BYTE "      ....,,,*,/*(                                            ", 13, 10
		BYTE "     ....,,,,,,,                                              ", 13, 10
		BYTE "      ....,,,                                                 ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 4] You caught a goldfish! You decided to put it back into the water", 13, 10
		BYTE "You gained $0 and 10 Experience", 13, 10, 0
	Lv5_Clam BYTE "                              ..                              ", 13, 10
		BYTE "                     .,*****,,,,*****,,..                     ", 13, 10
		BYTE "               ,**,,,,*,,..,,,,,,,****,,*,*                   ", 13, 10
		BYTE "            ,***,,,,.,,*,,,*,.,...,,***,**,,.                 ", 13, 10
		BYTE "          */***,///*,.............,.*.,*/,*,,,                ", 13, 10
		BYTE "           ******,,*,.*/*/***....,.,,,....,,,,,,,             ", 13, 10
		BYTE "           ,*,,,**,.,*,,,**.,....,/*,*,,,*,,//,*..            ", 13, 10
		BYTE "           ,,*(((%%..,*,..,.,. ..**,,***,*****,,**            ", 13, 10
		BYTE "             ,*/((((((%%&&&&&&,.....,,,,,,(((//%#.            ", 13, 10
		BYTE "                .,//(((#(##&&&&&%%%%##((/*..,,,,..            ", 13, 10
		BYTE "                   .*..*/*///(/,/(((((//*,.........           ", 13, 10
		BYTE "                       ..*/(###%%%%%###(/*,,,.......          ", 13, 10
		BYTE "                                               .....          ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 5] You caught a Clam! There's no pearl inside", 13, 10
		BYTE "You gained $1 and 15 Experience", 13, 10, 0
	Lv6_Shrimp BYTE "             ,////////////,                                   ", 13, 10
		BYTE "         (/////////////////////(((,                           ", 13, 10
		BYTE "      /////(//////(/////////////////(((((                     ", 13, 10
		BYTE "    (///////////////(/////////////////@@@/*   ..              ", 13, 10
		BYTE "  ,///(//////(///////.(((//////////////////////               ", 13, 10
		BYTE "  /////////////(//((/*        .*/(///,.            (          ", 13, 10
		BYTE " ///////////////////*/ .*            .                 .      ", 13, 10
		BYTE "  ((////////////////, // .      *////                    *.   ", 13, 10
		BYTE "  ///////////////.,.         ////(///                      .  ", 13, 10
		BYTE "   ////////////(//        *///(/////                        * ", 13, 10
		BYTE "    //((////////////,   /////////                             ", 13, 10
		BYTE "     /////////////////////////                              . ", 13, 10
		BYTE "       .//////////////////,                                   ", 13, 10
		BYTE "             ,((///(*.                                    .   ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 6] You caught a Shrimp! It's time for Nigiri Sushi perhaps", 13, 10
		BYTE "You gained $5 and 25 Experience", 13, 10, 0
	Lv7_Crab BYTE "           *.,***/****                   (**/(***,.*          ", 13, 10
		BYTE "        *,*/*****/                           /****//*,,       ", 13, 10
		BYTE "      /,*/(%&%*  (/.                       (*(  (%@#(/*,/     ", 13, 10
		BYTE "    **/,*////**.**                           /*.**////*/**.   ", 13, 10
		BYTE "     (*/((##&@                                   @%##(//*(    ", 13, 10
		BYTE "     ,(#%#%%                                       %%#%#(*    ", 13, 10
		BYTE "     (***/,*.         **/***/     /***(,(         (*,/***%    ", 13, 10
		BYTE "    //((##&/,**,(/.,/%/&#,,......,,.,,#&/#//.(/***,(&(#((//   ", 13, 10
		BYTE "     #/((/(//%(/#////(#(/***..,,,,.**/*(##(//(#(%%*((/((*%    ", 13, 10
		BYTE "         #%    ((///*(%#*/*/*,,,,,*//(*#%(/////(,   #(        ", 13, 10
		BYTE "           @%#(((((/(((##,*(/**,*,/(*,##(((/((//(#%&.         ", 13, 10
		BYTE "               /(#/**/%//(##((**/(((&((/%/*,(#((              ", 13, 10
		BYTE "           ,%*(((##((*,*///###//*#%#(//***((%(/#/*(,          ", 13, 10
		BYTE "        */     ,*//  (/////%&##(##%%///((#. %**,     /*       ", 13, 10
		BYTE "      /    ,*(,    (/(   %((%(##%#%((%.  (**    /(/,    *     ", 13, 10
		BYTE "          ,/     ,**        &#%%%%&        ***     #,         ", 13, 10
		BYTE "         /    /,*#                           %*/.    /        ", 13, 10
		BYTE "        (      *(                             (/      #       ", 13, 10
		BYTE "          /     #/                           /#     (         ", 13, 10
		BYTE "                  %/((                   %#/#                 ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 7] You caught a Crab! Sorry Mr.Crabs!", 13, 10
		BYTE "You gained $10 and 50 Experience", 13, 10, 0
	Lv8_Cod BYTE "                        **(///*                               ", 13, 10
		BYTE "                  .,/(/((((//* ,///*/////*/     **      .///  ", 13, 10
		BYTE "          ,//#/****,/**////*/**/((/**,/*#/((/(*(*/   (##(((*  ", 13, 10
		BYTE "     .*(//#(((((*,*,,*,**,*/*,,*(  .....(/*,*,*/(/,//%#((#(,  ", 13, 10
		BYTE "  (,,,**&/,****///,.//**,,..,,,,.,.,,.,,,,,..,,,,,,.*%#((((.  ", 13, 10
		BYTE "   */,.... .,,,*/..,,..  .   ..... ..... .,,*,/(((     (((//  ", 13, 10
		BYTE "         (((/*,..,.           .,..,..////*    /(//            ", 13, 10
		BYTE "                 //((....      .**,***,                       ", 13, 10
		BYTE "                 ,.,/*                                        ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 8] You caught a Cod! (The fish, not Call of Duty)", 13, 10
		BYTE "You gained $20 and 100 Experience", 13, 10, 0
	Lv9_Trout BYTE "                              (*(                             ", 13, 10
		BYTE "                           %///***,                           ", 13, 10
		BYTE "                %%%%%##/#/##((&%%.                      #(/   ", 13, 10
		BYTE "        ##%#(#(####(%*(%%%(/////***,(/(/(##%(%#####(((##/*,   ", 13, 10
		BYTE "   ((/(# **//,,*((*%*(,*,*#/*,*/#*(*//////*//#***/(/,,///*,   ", 13, 10
		BYTE "    *,,,.,,.**,/#(/((*/,**/.///*/*///////****,*( /*//(((*,*   ", 13, 10
		BYTE "              .(/*///***,,,,***(((/////  /#(///**     #((/*   ", 13, 10
		BYTE "                                 (*,       .(/*/              ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 9] You caught a Trout! Colorful!", 13, 10
		BYTE "You gained $40 and 150 Experience", 13, 10, 0
	Lv10_Sardine BYTE "               ,/((%#/####((/(//*(#((%(#%#/                   ", 13, 10
		BYTE "     *//**//**.. .        .....              .**/(%/*         ", 13, 10
		BYTE "    ,...*..*/*,.,***/**/,/**/,/***********,,.,,,**///#*,,     ", 13, 10
		BYTE "        *,,,..,,,,/.,,.,,,,,,,,.........            ,//       ", 13, 10
		BYTE "                  ,,,,..                                /     ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 10] You caught a Sardine! A Sardine that Grows From the Soil", 13, 10
		BYTE "You gained $80 and 200 Experience", 13, 10, 0
	Lv11_Lobster BYTE "       %#%#%##%%&&&&&&                                        ", 13, 10
		BYTE "     #(((/(#(((##%%&&%&&  &#    #   ((                        ", 13, 10
		BYTE "    #(##%%%#((%(/##%%%#%&#   (/ (  ,(   .(                    ", 13, 10
		BYTE "    %%. (%(/((/&&%%%&  %%%&%   # ##%%  /               *      ", 13, 10
		BYTE "      (####%            #%%#%& (% % % #              ###(%    ", 13, 10
		BYTE "                        ( /&&&&&&&&%&&&%%%%%%&%%%%%&%%(###(   ", 13, 10
		BYTE "                      /(#%%%%%%%%##%%#%%%%%%%%%%%%%#%%#((#%   ", 13, 10
		BYTE "                    .  %,(/##((((///((#///((//((/((/#((##%(   ", 13, 10
		BYTE "                         %%%%&  % & &%%             /((//%    ", 13, 10
		BYTE "    .#(((#%%%          (#%(%   ##%/ % %              ///#     ", 13, 10
		BYTE "    #(((%%%##(##(#(/#%###%    #%%# ,(  ./                     ", 13, 10
		BYTE "     (##(#((#((#(//(##%&   /((  (   (      #                  ", 13, 10
		BYTE "       .%%%%%%%%##%&%&         ,     %                        ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 11] You caught a Lobster! Huge Shrimp!", 13, 10
		BYTE "You gained $120 and 500 Experience", 13, 10, 0
	Lv12_Tuna BYTE "                                  ,                           ", 13, 10
		BYTE "                                 (%                           ", 13, 10
		BYTE "                                 %(#%%                        ", 13, 10
		BYTE "                        /%@@@&&&%%###*%     /                 ", 13, 10
		BYTE "                &%%%%&&&@@@@@@@@@@@@@&&&#&  &%                ", 13, 10
		BYTE "           /%%(@@%&/**/******/***///(#&@@@&&@%                ", 13, 10
		BYTE "       @*&** /, ..,/,,.. ,.......,,,,****/#(@@&&&%%%%%&       ", 13, 10
		BYTE "         &(#%&&#..,,.. ..( ., , *,%@@&%#####*(%@&             ", 13, 10
		BYTE "         (%##((/*,,.,*,..,,,*&.*####/(#/...,,,*/%@            ", 13, 10
		BYTE "            *(#%((///**(%%(.....*((((/,,,,*,,.,*/(&           ", 13, 10
		BYTE "                   ((((((/#((*,###(**((((*/**,**//(&          ", 13, 10
		BYTE "                             (%&##%#(####(#(###(((#&          ", 13, 10
		BYTE "                               #    &&     ((###%%%&          ", 13, 10
		BYTE "                                %             %%&#%%          ", 13, 10
		BYTE "                                              &(#%*#          ", 13, 10
		BYTE "                                      &#     &##%(# #         ", 13, 10
		BYTE "                                       &&   &(##      #       ", 13, 10
		BYTE "                                        %&%&#                 ", 13, 10
		BYTE "                                        &&,                   ", 13, 10
		BYTE "                                       &@                     ", 13, 10
		BYTE "                                      &@                      ", 13, 10
		BYTE "                                     @                        ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 12] You caught a Tuna! It is bluefin, and expensive!", 13, 10
		BYTE "You gained $180 and 750 Experience", 13, 10, 0
	Lv13_Salmon BYTE "                                                                         .&       ", 13, 10
		BYTE "                                         %##%                          (###       ", 13, 10
		BYTE "                               .,,*,*((/////(#&                      #%*(((       ", 13, 10
		BYTE "      @#(%*/***/*(,////((*/**/*//#//*(*///**((/              .     .(***,((,      ", 13, 10
		BYTE "         ##/. .....,,.,,.*,,**,,,,*****,(/**/**,%,*///***,****///#/****/*//#      ", 13, 10
		BYTE "          /(,. ...../.,,..,,,,,,,,..,,,,,,,,,,.,.,,,,,,,.,.,,,*,,,,,,*(/,//%      ", 13, 10
		BYTE "      ,#%%%####(*,//((&&%%%%#*,,,,.,.,,..*.,,,,,,,,,,,**,***/*/*////(/%((,/#&     ", 13, 10
		BYTE "           (#(%(/##//((##%%((/**,,,,,,,,*,,**********//////**#%*        &&/((%    ", 13, 10
		BYTE "                  /((((#(#(((///////*//*/////((//////**(##(#(#                    ", 13, 10
		BYTE "                   %%%%      .((/////((*(%#((*       (####(*                      ", 13, 10
		BYTE "                    &                   ##(#           ((                         ", 13, 10
		BYTE "                                         #(*                                      ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 13] You caught a Salmon! Its bright orange meat makes you hungry!", 13, 10
		BYTE "You gained $230 and 1000 Experience", 13, 10, 0
	Lv14_Swordfish BYTE "              &                                                                                       ", 13, 10
		BYTE "               %#                                                                         ..@         ", 13, 10
		BYTE "                #/                                @%#,                             ..@..**            ", 13, 10
		BYTE "                (#(                                 #%##                   .***@****                  ", 13, 10
		BYTE "               /./(                                @&&@&&&&&&&&%%%&&@@&&/***                          ", 13, 10
		BYTE "             @##/%%%(.            ........,*/(#%%&&&&&%(((#(..,.,@%(                                  ", 13, 10
		BYTE "        .%//#%%@   ,(((*.  ...,.,*///(((((((/*,,,,,....,,*%.,,*((#                                    ", 13, 10
		BYTE "                       /(####(///*,****,,*,*,,,,  . .,****/(&%%%***/%.                                ", 13, 10
		BYTE "                            /(#########(((((((///(/(((///(*%%**/.                                     ", 13, 10
		BYTE "                                &&%((((((((((((#########(#%&(                                         ", 13, 10
		BYTE "                                (##                     #&@@                                          ", 13, 10
		BYTE "                              &@                     .,  @@                                           ", 13, 10
		BYTE "                                                       &@                                             ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 14] You caught a Swordfish! Almost get pierced by it!", 13, 10
		BYTE "You gained $300 and 1500 Experience", 13, 10, 0
	Lv15_GoldenCarp BYTE "                              *                               ", 13, 10
		BYTE "                            /*,. ,                            ", 13, 10
		BYTE "                    .//*(//%#%###%**(*,/,*                    ", 13, 10
		BYTE "              (%%&//#%&.,,,,,*,*/*(/%%*%%((**         (##%#   ", 13, 10
		BYTE "           *%%%/**%%/,,*,(*,.,/#(##/,,*,((*(@&    *(((%%%(#   ", 13, 10
		BYTE "        /%%%&%(#*,,/,,%/.,&*,./*,*(#%,,,,(%#,/*/#((%%%###(    ", 13, 10
		BYTE "     (#%.%#%%(#/%.**. , /.../, ..,/*,..,*..(.,#,*/%#%%##/     ", 13, 10
		BYTE "     **/(((#((/#.,....,.  ,. ,,.. .,,,,.,*,.,,,. (###%%%##    ", 13, 10
		BYTE "            ..,...**/#.. ........,..,..,**(((,      #//###%   ", 13, 10
		BYTE "                  (#((((/.                /%/*         ###&   ", 13, 10
		BYTE "                   ((//*                    *                 ", 13, 10, 13, 10, 13, 10
		BYTE "[Tier 15] You caught a Golden Carp! How does it even exist? I'mma just be rich!", 13, 10
		BYTE "You gained $1000 and 3000 Experience", 13, 10, 0

.code
;------------------------------------------------
Fish_Show PROC,
	Lvl:DWORD
;	
;	Receives: Level (DWORD) - The level of fish caught. Must greater than or equal to 0. Anything after 15 is considered lvl15
;	Return: EBX - Money earned
;			ECX - Experience gained

	CMP Lvl, 0
	JE Lv0_Fail_l
	CMP Lvl, 1
	JE Lv1_TinCan_l
	CMP Lvl, 2
	JE Lv2_Seaweed_l
	CMP Lvl, 3
	JE Lv3_Boots_l
	CMP Lvl, 4
	JE Lv4_Goldfish_l
	CMP Lvl, 5
	JE Lv5_Clam_l
	CMP Lvl, 6
	JE Lv6_Shrimp_l
	CMP Lvl, 7
	JE Lv7_Crab_l
	CMP Lvl, 8
	JE Lv8_Cod_l
	CMP Lvl, 9
	JE Lv9_Trout_l
	CMP Lvl, 10
	JE Lv10_Sardine_l
	CMP Lvl, 11
	JE Lv11_Lobster_l
	CMP Lvl, 12
	JE Lv12_Tuna_l
	CMP Lvl, 13
	JE Lv13_Salmon_l
	CMP Lvl, 14
	JE Lv14_Swordfish_l
	CMP Lvl, 15
	JGE Lv15_GoldenCarp_l

Lv0_Fail_l:
	MOV EDX, OFFSET Lv0_Fail
	MOV EBX, 0
	MOV ECX, 0
	JMP Finally
Lv1_TinCan_l:
	MOV EDX, OFFSET Lv1_TinCan
	MOV EBX, 0
	MOV ECX, 1
	JMP Finally
Lv2_Seaweed_l:
	MOV EAX, lightGreen+(black*16)
	CALL SetTextColor
	MOV EDX, OFFSET Lv2_Seaweed
	MOV EBX, 0
	MOV ECX, 3
	JMP Finally
Lv3_Boots_l:
	MOV EAX, lightGray+(black*16)
	CALL SetTextColor
	MOV EDX, OFFSET Lv3_Boots
	MOV EBX, 0
	MOV ECX, 5
	JMP Finally
Lv4_Goldfish_l:
	MOV EDX, OFFSET Lv4_Goldfish
	MOV EBX, 0
	MOV ECX, 10
	JMP Finally
Lv5_Clam_l:
	MOV EDX, OFFSET Lv5_Clam
	MOV EBX, 1
	MOV ECX, 15
	JMP Finally
Lv6_Shrimp_l:
	MOV EAX, lightRed+(black*16)
	CALL SetTextColor
	MOV EDX, OFFSET Lv6_Shrimp
	MOV EBX, 5
	MOV ECX, 25
	JMP Finally
Lv7_Crab_l:
	MOV EAX, lightRed+(black*16)
	CALL SetTextColor
	MOV EDX, OFFSET Lv7_Crab
	MOV EBX, 10
	MOV ECX, 50
	JMP Finally
Lv8_Cod_l:
	MOV EDX, OFFSET Lv8_Cod
	MOV EBX, 20
	MOV ECX, 100
	JMP Finally
Lv9_Trout_l:
	MOV EDX, OFFSET Lv9_Trout
	MOV EBX, 40
	MOV ECX, 150
	JMP Finally
Lv10_Sardine_l:
	MOV EDX, OFFSET Lv10_Sardine
	MOV EBX, 80
	MOV ECX, 200
	JMP Finally
Lv11_Lobster_l:
	MOV EAX, lightRed+(black*16)
	CALL SetTextColor
	MOV EDX, OFFSET Lv11_Lobster
	MOV EBX, 120
	MOV ECX, 500
	JMP Finally
Lv12_Tuna_l:
	MOV EDX, OFFSET Lv12_Tuna
	MOV EBX, 180
	MOV ECX, 750
	JMP Finally
Lv13_Salmon_l:
	MOV EDX, OFFSET Lv13_Salmon
	MOV EBX, 230
	MOV ECX, 1000
	JMP Finally
Lv14_Swordfish_l:
	MOV EDX, OFFSET Lv14_Swordfish
	MOV EBX, 300
	MOV ECX, 1500
	JMP Finally
Lv15_GoldenCarp_l:
	MOV EAX, yellow+(black*16)
	CALL SetTextColor
	MOV EDX, OFFSET Lv15_GoldenCarp
	MOV EBX, 1000
	MOV ECX, 3000

Finally:
	CALL WriteString
	MOV EAX, white+(black*16)
	CALL SetTextColor

	RET
Fish_Show ENDP


END