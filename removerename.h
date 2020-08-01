#include <stdio.h>

void remove_rename()
{
		int res1=remove("records.txt");
		int res2=rename("temp.txt","records.txt");
		
      		
			if ( res1 != 0 )																			/* error check incase the remove function doesn't work */
    		{
				perror( "Error deleting file" );
  			}
  			if ( res2 != 0)
  			{
  				perror("Error renameing file");	
			}
}


