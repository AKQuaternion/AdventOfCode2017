//
// Created by Chris Hartman on 11/20/19.
//
#include <iostream>
#include <string>
using std::cout;
using std::string;

const static string INPUT =
    "32941994713271959948248321975648598766826381888897682988942438326656546814"
    "12886862234525991553276578641265589959178414218389329361496673991614673626"
    "34455217941399556226681813837239321396614312491446939769258725111266321786"
    "28792332267635339111288933545363532138471222514638578941598198287248279695"
    "76432191847787772732881266875469721189331882228146576832921314638221317393"
    "25647199859811728963268466335527384598393384572171349781176699536779585796"
    "52221836687655174542633541111348413346313451115961316827261965747631651878"
    "89337599583345634413436165539744188866156771585647718555182529936669683581"
    "66239861876539148716471572484989456331442695934811928695514443945273176266"
    "65687416121532544691317241376998329847289378659567119255926284566171336952"
    "59554548719328229938621332325125972547181236812263887375866231118312954369"
    "43293735935726646738331832623957287731476512184483112617817398879976521891"
    "31788259662688164765597929473599568599892289171362671785717763163452925734"
    "89873792149646548747995389669692188457724414468727192819919448275922166321"
    "15814136523754522263368837289145184243445852769877434211148249899938383149"
    "25776151545912787196567982773773632843794687579983731932317957676446541554"
    "32692988651312845433511879457921638934877557575241394363721667237778962455"
    "96149355984852258241374821897121248637323279587836296487385599469714969282"
    "49171833755451921194535873981999125644746142199293451854686611299663796938"
    "13498542474732198176496694746111576925715493967296487258237854152382365579"
    "87689439181575981537331915921347555525148875427988824549237359547118919135"
    "32446846976628483765298815125292216273135274412214596727869231451659896112"
    "23372241149929436247374818467481641931872972582295425936998535194423916544"
    "36779952227691444523158227236838883183443756275211932528647435286355469337"
    "37188486495684517977519263156175752953819644268436252828195247471197268721"
    "93569785611959896776143539915299968276374712996485367853494734376257511273"
    "44373643346449628721961569734197313171516676891614982839645463859671357296"
    "3686159214116763";

void day1() {
  auto sum1 = 0;
  auto sum2 = 0;
  for (int i = 0; i < INPUT.size(); ++i) {
    if (INPUT[i] == INPUT[(i + 1) % INPUT.size()])
      sum1 += INPUT[i] - '0';
    if (INPUT[i] == INPUT[(i + INPUT.size() / 2) % INPUT.size()])
      sum2 += INPUT[i] - '0';
  }
  cout << "Day 1 star 1 = " << sum1 << "\n";
  cout << "Day 1 star 2 = " << sum2 << "\n";
}