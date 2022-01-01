#include "hydraModel.h"
#include "hydraController.h"

using namespace std;

int main (int argc, char **argv) {
   bool testingMode = 0;
   int howManyPlayers;
   
   // ask for the number of players
   cout << "How many players?" << endl;
   
   // and take the input received, and enter a fresh line after
   cin >> howManyPlayers;
   cout << endl;

   // check if the testing command has been entered
   //    and enable testing mode if so
   if (argc > 1) {
      string possibleArg = string(argv[1]);
      if (possibleArg == "-testing") {
         testingMode = 1;
      }
   }
   // create our heap-allocated HydraController and HydraModel objects
   auto model = make_unique<HydraModel>(howManyPlayers, testingMode);
   // initialize the model 
   model->init();
   // now we initialize the controller with the
   //    model's address
   HydraModel * theModel = model.get();
   auto controller = make_unique<HydraController>(theModel, howManyPlayers, testingMode);
   // now we run the game inside the HydraController
   controller->runGame();

} 