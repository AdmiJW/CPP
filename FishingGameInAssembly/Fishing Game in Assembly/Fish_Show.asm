
TITLE Showing the Fish Catched by Level

INCLUDE Irvine32.inc

.data

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
		BYTE "                     / . .,*(####(/*... /                     ", 13, 10, 0
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
		BYTE "                           .%#%%&#.                           ", 13, 10, 0
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
		BYTE "                                (####((/((,                   ", 13, 10, 0
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
		BYTE "      ....,,,                                                 ", 13, 10, 0
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
		BYTE "                                               .....          ", 13, 10, 0
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
		BYTE "             ,((///(*.                                    .   ", 13, 10, 0
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
		BYTE "                  %/((                   %#/#                 ", 13, 10, 0
	Lv8_Cod BYTE "                        **(///*                               ", 13, 10
		BYTE "                  .,/(/((((//* ,///*/////*/     **      .///  ", 13, 10
		BYTE "          ,//#/****,/**////*/**/((/**,/*#/((/(*(*/   (##(((*  ", 13, 10
		BYTE "     .*(//#(((((*,*,,*,**,*/*,,*(  .....(/*,*,*/(/,//%#((#(,  ", 13, 10
		BYTE "  (,,,**&/,****///,.//**,,..,,,,.,.,,.,,,,,..,,,,,,.*%#((((.  ", 13, 10
		BYTE "   */,.... .,,,*/..,,..  .   ..... ..... .,,*,/(((     (((//  ", 13, 10
		BYTE "         (((/*,..,.           .,..,..////*    /(//            ", 13, 10
		BYTE "                 //((....      .**,***,                       ", 13, 10
		BYTE "                 ,.,/*                                        ", 13, 10, 0
	Lv9_Trout BYTE "                              (*(                             ", 13, 10
		BYTE "                           %///***,                           ", 13, 10
		BYTE "                %%%%%##/#/##((&%%.                      #(/   ", 13, 10
		BYTE "        ##%#(#(####(%*(%%%(/////***,(/(/(##%(%#####(((##/*,   ", 13, 10
		BYTE "   ((/(# **//,,*((*%*(,*,*#/*,*/#*(*//////*//#***/(/,,///*,   ", 13, 10
		BYTE "    *,,,.,,.**,/#(/((*/,**/.///*/*///////****,*( /*//(((*,*   ", 13, 10
		BYTE "              .(/*///***,,,,***(((/////  /#(///**     #((/*   ", 13, 10
		BYTE "                                 (*,       .(/*/              ", 13, 10, 0
	Lv10_Sardine BYTE "               ,/((%#/####((/(//*(#((%(#%#/                   ", 13, 10
		BYTE "     *//**//**.. .        .....              .**/(%/*         ", 13, 10
		BYTE "    ,...*..*/*,.,***/**/,/**/,/***********,,.,,,**///#*,,     ", 13, 10
		BYTE "        *,,,..,,,,/.,,.,,,,,,,,.........            ,//       ", 13, 10
		BYTE "                  ,,,,..                                /     ", 13, 10, 0
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
		BYTE "       .%%%%%%%%##%&%&         ,     %                        ", 13, 10, 0
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
		BYTE "                                     @                        ", 13, 10, 0
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
		BYTE "                                         #(*                                      ", 13, 10, 0
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
		BYTE "                                                       &@                                             ", 13, 10, 0
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
		BYTE "                   ((//*                    *                 ", 13, 10, 0

.code

Fish_Show PROC
	MOV EDX, OFFSET Lv1_TinCan
	CALL WriteString

	RET


Fish_Show ENDP


END