using EntityFrameworkCore.Projectables;

namespace Geld_Guardian.Pages.Data.Models
{
    public class BillItem
    {
        public int BillItemId { get; set; }
        public int BillId { get; set; } // Foreign key to Bill
        public string Description { get; set; }
        public int CategoryId { get; set; } = 1;
        public int Quantity { get; set; }
        public decimal UnitPrice { get; set; }
        [Projectable]
        public decimal TotalPrice => (Quantity * UnitPrice); // Calculated property

        // Navigation property back to the Bill
        public Bill Bill { get; set; }
        public Categorie Category { get; set; }
    }
}
