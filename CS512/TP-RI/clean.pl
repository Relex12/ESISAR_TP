 #!/usr/bin/perl -w
use utf8;

#clean.pl
#AMC 
 #ouvre la liste des fichiers dans Collection
 #ouvre le contenu de chaque fichier et le passe en minuscule sans accents et pontuactions
 use open ':locale';
 
 open(COLL,"Collection/Collection") || die ("Erreur d'ouverture du fichier de fichierAlire") ;
 
 while (<COLL>) {
	$_ =~ s/\n//g;
	$fic = $_;
	
	open(CACM,"<Collection/$fic") || die ("Erreur d'ouverture du fichier de fichierAlire") ;
	open(F,">Collection/$fic.flt") || die ("Erreur d'ouverture du fichier de fichierAEcrire") ;
	while (<CACM>) {
		$_ =~ s/\n/ /g;
		$_ =~ tr/àâäéèêëîïù/aaaeeeeiiu/;
		$_ =~ s/(\"|\,|\=|\/|\.|\?|\'|\(|\)|\_|\$|\%|\+|\[|\]|\{|\}|\&|\;|\:|\~|\!|\@|\#|\^|\*|\||\<|\>|\-|\\s|\\)/ /g;
		$_ =~ s/\s+/ /g; # on enleve les espaces crees qui ne servent à rien
		
		print F lc($_);
	}
	close(CACM);
	close(F);
 }
 close(COLL);
 
