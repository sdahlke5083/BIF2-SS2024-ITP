namespace Geld_Guardian.Pages.Data.Models
{
    public class BillItem
    {
        public int BillItemId { get; set; }
        public int BillId { get; set; } // Foreign key to Bill
        public string Description { get; set; }
        public string Category { get; set; }
        public int Quantity { get; set; }
        public decimal UnitPrice { get; set; }
        public decimal TotalPrice => Quantity * UnitPrice; // Calculated property

        // Navigation property back to the Bill
        public Bill Bill { get; set; }
    }
}
