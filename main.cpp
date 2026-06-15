#include <iostream>
#include <cmath>
using namespace std;

int calculate_hex_area(int width) {
   return (sqrt(3) * (width * width)) / 2;
}

int calculate_hectares(int area) {
    // 1 square mile = 258.999 hectares
    return area * 258.999;
}

int apply_region_type(int &hectares, int &yield_ratio) {
    int region_type = 0;
    cout << "The types of regions are: \n";
    cout << "1. River deltas and floodplains\n";
    cout << "8:1 yield ratio, 80\% Arable land\n";
    cout << "2. Flat temperate plains\n";
    cout << "4:1 yield ratio, 60\% Arable land\n";
    cout << "3. Heavy clay soils, Midlands and deep interiors\n";
    cout << "3:1 yield ratio, 40\% Arable land\n";
    cout << "4. Chalk/sandy soils, arid scrublands, coastal plains, and limestone hills.\n";
    cout << "2:1 yield ratio, 20\% Arable land\n";
    cout << "5. Mountainous regions, highlands, and rocky terrain.\n";
    cout << "1:1 yield ratio, 10\% Arable land\n";

    cout << "Enter the region type (1-5): ";
    cin >> region_type;

    switch (region_type){
        case 1:
            hectares *= 0.8;
            yield_ratio = 8;
            cout << "You selected River deltas and floodplains\n";
            break;
        case 2:
            hectares *= 0.6;
            yield_ratio = 4;
            cout << "You selected Flat temperate plains\n";
            break;
        case 3:
            hectares *= 0.4;
            yield_ratio = 3;
            cout << "You selected Heavy clay soils, Midlands and deep interiors\n";
            break;
        case 4:
            hectares *= 0.2;
            yield_ratio = 2;
            cout << "You selected Chalk/sandy soils, arid scrublands, coastal plains, and limestone hills.\n";
            break;
        case 5:
            hectares *= 0.1;
            yield_ratio = 1;
            cout << "You selected Mountainous regions, highlands, and rocky terrain.\n";
            break;
        default:
            cout << "Invalid region type.\n";
    }
    return region_type;
}

int set_plot_size(int region_type){
   int plot_size = 12;
   if(region_type == 1){
        plot_size = 6;
   }
return plot_size;
}

int calculate_farm_families(int hectares, int plot_size) {
   int families = 0;
   families = (hectares / plot_size);
   return families;
}

int calculate_grain_surplus(int families, int plot_size, int yield_ratio) {
    int rotation_system = 0;
    float rotation_multiplier = 0;
    int output = 0;
    int gross_output = 0;
    int nobel_tax = 0; 
    float church_tax = 0;
    int seeds = 0; 
    cout << "Please enter a rotation system (1-3): \n";
    cout << "1. Two-field system(50\% of land cultivated)\n";
    cout << "2. Three-field system(66\% of land cultivated)\n";
    cout << "3. Floodplain (100\% of land cultivated)\n";
    cin >> rotation_system;
    switch(rotation_system){
        case 1:
            cout << "You selected Two-field system\n";
            rotation_multiplier = 0.5;
            break;
        case 2:
            cout << "You selected Three-field system\n";
            rotation_multiplier = 0.66;
            break;
        case 3:
            cout << "You selected Floodplain\n";
            rotation_multiplier = 1.0;
            break;
        default:
            cout << "Invalid rotation system.\n";
            return 0;
    }
    gross_output = families * (plot_size * rotation_multiplier) * 6 * yield_ratio;
    
    cout << "Gross output before taxes and losses: " << gross_output << "\n";
    cout << "How much does the nobel take as tax(buckets per family)? flat number: \n";
    cin >> nobel_tax;
    cout << "How much does the church take as tax? percentage enter as a decimal: \n";
    cin >> church_tax;
    output = gross_output - (nobel_tax * families);
    output = output - (gross_output * church_tax);
    // 20% loss due to spoilage, pests, and other factors
    output = output - (output * 0.2);
    // seeds for next year
    seeds = families * (plot_size * rotation_multiplier) * 6;
    output -= seeds; 
    //substance cut
    output -= families * 40;
    // 20% cut for rural towns
    if(output > 0){
        output -= output * 0.2; 
    }
    // nobbles take a flat amount but some of it ends up on the market so we add it back in
    output += (nobel_tax * families) * 0.2; 

    return output;
}

int calculate_transit_loss(int region_grain) {
    int input = 0;
    int total_loss = 0;
    cout << "What is the distance to collection point in miles? \n";
    cout << "If the grain surplus goes straight to the city, enter 0\n";
    cin >> input;
    total_loss += (region_grain * 0.002) * input;
    cout << "What is the distance from collection point to city in miles? \n";
    cin >> input;
    total_loss += (region_grain * 0.002) * input;
    cout << "Does the grain travel by river? (1 for yes, 0 for no) \n";
    cin >> input;
    if(input == 1){
        total_loss += (region_grain * 0.04);
    }
    cout << "How many tolls on the route? \n";
    cin >> input;
    total_loss += (region_grain * 0.01) * input;
    cout << "How many river crossings on the route? \n";
    cin >> input;
    total_loss += (region_grain * 0.03) * input;

    return total_loss;
}

int main() {
    int regions = 0;
    int hex_width = 0;
    int total_grain = 0;
    int max_population = 0;
    

    cout << "Enter the number of regions: \n";
    cin >> regions;
    cout << "Enter the width of the hexes in miles: \n";
    cin >> hex_width;

    for(int i = 0; i < regions; i++){
        int hexs = 0;
        int region_area = 0;
        int hectares = 0;
        int yield_ratio = 0;
        int region_type = 0;
        int farm_families = 0;
        int plot_size = 0;
        int region_grain = 0;
        int lost_grain = 0;

        cout << "Enter number of hexs in region " << i+1 << ": ";
        cin >> hexs;
        region_area = hexs * calculate_hex_area(hex_width);
        cout << "Area of region " << i+1 << ": " << region_area << " square miles\n";
        hectares = calculate_hectares(region_area);
        cout << "Area of region in hectares " << i+1 << ": " << hectares << "\n";

        region_type = apply_region_type(hectares, yield_ratio);
        plot_size = set_plot_size(region_type);
        farm_families = calculate_farm_families(hectares, plot_size);
        cout << "number of farm families in region " << i+1 << ": " << farm_families << "\n";
        cout << "total rural population in region " << i+1 << ": " << farm_families *5 << "\n";
        region_grain = calculate_grain_surplus(farm_families, plot_size, yield_ratio);
        cout << "grain surplus in region " << i+1 << ": " << region_grain << "\n";
        lost_grain = calculate_transit_loss(region_grain);
        cout << "grain lost during transit in region " << i+1 << ": " << lost_grain << "\n";
        region_grain -= lost_grain;

        total_grain += region_grain;
    }
    total_grain = total_grain - (total_grain * 0.15); // 15% to granaries and reserves
    cout << "Total grain surplus: " << total_grain << "\n";
    max_population = (total_grain / 10);
    cout << "Maximum population that can be supported: " << max_population << "\n";

    return 0;
}