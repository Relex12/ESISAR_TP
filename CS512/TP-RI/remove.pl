##AMC
##remove.pl
# Écrire une fonction qui ouvre les fichiers CACM-XX.flt un à un
# et qui applique le stop-list common-words en enlevant tous les termes de ces fichiers qui y apparaissent.

# Le résultat du filtrage sera mis dans un fichier portant le même nom
# que ces fichiers avec une nouvelle extension .stp

# Indication: On pourra utiliser une table de hash en parcourant le fichier common-words
# et en associant à chaque terme de fichier pris comme une clé de la table, la valeur 1.
# Le filtrage se fera en regardant si un terme des fichiers CACM-XX.flt est une clé de cette table de hash ou non.

#parcours de common-words

my %swords;
open(STOPW,"cacm/common_words") || die ("Erreur d'ouverture du fichier de fichierAlire") ;
while (<STOPW>) {
	$_ =~ s/\n//g;
	$swords{$_}=1;
}

while ( my ($cle,$val)=each(%swords) ) {
		 print "motvide: $cle, value: $val\n";

}

open(COLL,"<Collection/Collection") || die ("Erreur d'ouverture du fichier de fichierAlire") ;
while (<COLL>) {
	$_ =~ s/\n//g;
	$fic = $_;

	open(F,"<Collection/$fic.flt") || die ("Erreur d'ouverture du fichier de fichierALire") ;
	open(STP,">Collection/$fic.stp") || die ("Erreur d'ouverture du fichier de fichierAEcrire") ;

	while (<F>) {
		$_ =~ s/\n//g;
		$_ =~ s/\s+/ /;

	#enlever les stop words
	@tab=split(/ /,$_);
	$nbvide = 0;
	foreach my $v (@tab) { #if exists $hash{$key}
		if (!$swords{$v}) { 		#le mot courant exist dans le hash, on ne l'écrit pas sinon on l'ecrit
			print STP $v . " ";
		}
		else { $nbvide++; print "(**". $v . " ";}
	}
	print $fic . " " . $nbvide . "\n";

	}
	close(F);
	close(STP);
 }
 close(COLL);
