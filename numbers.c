void numbers() {

   printf( "\n Here we have nodigi case (1), digi with 20%% case (2) and digi(60%%) with 60%% case (3). \n" );

   const Int_t n = 9;

   Float_t energy[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t meanerror[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigma[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigmaerror[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   Float_t value[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };   // 1 and 2

   Float_t energy2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t meanerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigma2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigmaerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   Float_t value2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };   // 2 and 3

   Float_t energy3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t meanerror3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigma3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigmaerror3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   Float_t value3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };   // 1 and 3

   float temp11 = 0;
   float temp12 = 0;
   float temp21 = 0;
   float temp22 = 0;
   float temp31 = 0;
   float temp32 = 0;
/*
   for (int i = 0; i < n; i++) {
     printf( " %f ", energy[i] );
     printf( " %f ", mean[i] );
     printf( " %f ", meanerror[i] );
     printf( " %f ", sigma[i] );
     printf( " %f ", sigmaerror[i] );

     printf( " %f ", value[i] );
     printf( "\n" );

     printf( " %f ", energy2[i] );
     printf( " %f ", mean2[i] );
     printf( " %f ", meanerror2[i] );
     printf( " %f ", sigma2[i] );
     printf( " %f ", sigmaerror2[i] );

     printf( " %f ", value2[i] );
     printf( "\n" );
   }
*/
   FILE *file = fopen("out_nodigi.txt", "r");
   if ( !(long)file ) return;

   FILE *file2 = fopen("out_digi.txt", "r");
   if ( !(long)file2 ) return;

   FILE *file3 = fopen("out_60digi.txt", "r");
   if ( !(long)file3 ) return;

  for ( int i = 0; i < n; i++ ) {
    fscanf( file, "%f %E %E %E %E %E %E\n", &energy[i], &mean[i], &meanerror[i], &sigma[i], &sigmaerror[i], &temp11, &temp12 );
    if ( feof( file ) ) break;
  }

  for ( int i = 0; i < n; i++ ) {
    fscanf( file2, "%f %E %E %E %E %E %E\n", &energy2[i], &mean2[i], &meanerror2[i], &sigma2[i], &sigmaerror2[i], &temp21, &temp22 );
    if ( feof( file2 ) ) break;
  }

  for ( int i = 0; i < n; i++ ) {
    fscanf( file3, "%f %E %E %E %E %E %E\n", &energy3[i], &mean3[i], &meanerror3[i], &sigma3[i], &sigmaerror3[i], &temp31, &temp32 );
    if ( feof( file3 ) ) break;
  }

  for ( int i = 0; i < n; i++ ) {
    value[ i ] = ( sigma2[i] / sigma[i] ) - 1.0;

    value2[ i ] = ( sigma3[i] / sigma2[i] ) - 1.0;

    value3[ i ] = ( sigma3[i] / sigma[i] ) - 1.0;
  }

   printf( "\n" );

   printf( " Data for nodigi and difference for nodigi and digi  " );

   printf( "\n" );

   for (int i = 0; i < n; i++) {
     printf( " %f ", energy[i] );
     printf( " %f ", mean[i] );
     printf( " %f ", meanerror[i] );
     printf( " %f ", sigma[i] );
     printf( " %f ", sigmaerror[i] );
     printf( " ||| " );
     printf( " %f (%f%%) ", value[i], value[i] * 100 );
     printf( "\n" );
   }

   printf( "\n" );

   printf( " Data for digi and difference for digi and digi(60%%)  " );

   printf( "\n" );

   for (int i = 0; i < n; i++) {
     printf( " %f ", energy2[i] );
     printf( " %f ", mean2[i] );
     printf( " %f ", meanerror2[i] );
     printf( " %f ", sigma2[i] );
     printf( " %f ", sigmaerror2[i] );
     printf( " ||| " );
     printf( " %f (%f%%) ", value2[i], value2[i] * 100 );
     printf( "\n" );
   }

   printf( "\n" );

   printf( " Data for digi(60%%) and difference for nodigi and digi(60%%)  " );

   printf( "\n" );

   for (int i = 0; i < n; i++) {
     printf( " %f ", energy3[i] );
     printf( " %f ", mean3[i] );
     printf( " %f ", meanerror3[i] );
     printf( " %f ", sigma3[i] );
     printf( " %f ", sigmaerror3[i] );
     printf( " ||| " );
     printf( " %f (%f%%) ", value3[i], value3[i] * 100 );
     printf( "\n" );
   }

   Float_t v1 = 0;
   Float_t v2 = 0;
   Float_t v3 = 0;

  for ( int i = 0; i < n; i++ ) v1 = v1 + value[i];
  for ( int i = 0; i < n; i++ ) v2 = v2 + value2[i];
  for ( int i = 0; i < n; i++ ) v3 = v3 + value3[i];

  v1 = v1 / n;
  v2 = v2 / n;
  v3 = v3 / n;

  printf( "\n" );

  printf( "Difference for 1 and 2 is %f (%f%%) \n", v1, v1 * 100);
  printf( "Difference for 2 and 3 is %f (%f%%) \n", v2, v2 * 100);
  printf( "Difference for 1 and 3 is %f (%f%%) \n", v3, v3 * 100);

  printf( " \n " );
 
}



