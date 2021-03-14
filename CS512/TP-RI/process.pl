open(COLL,"Collection/Collection") || die ("Erreur d'ouverture du fichier de fichierAlire") ;

open(F,">cacm/nbmot.txt") || die ("Erreur d'ouverture du fichier de fichierAEcrire") ;

 my %words;
 while (<COLL>) {
    $_ =~s/\n//g;
    $fic = $_;

    open(CACM,"<Collection/$fic.stp") || die ("Erreur d'ouverture du fichier de fichierAlire") ;

    while (<CACM>) {
        $_ =~s/\n//g;
        foreach(split /\s+/,$_){
            $words{$_}++;
        }
    }
    close(CACM);
 }
 close(COLL);
 foreach(sort{$words{$b} <=> $words{$a}} (keys %words)) {
     $compt++;
    print F $compt . " " . $words{$_} . " " . $_ . "\n";
 }
 close(F);
