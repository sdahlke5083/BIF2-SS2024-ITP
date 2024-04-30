using System.Collections.Generic;
using System;
using Microsoft.EntityFrameworkCore;
using System.ComponentModel.DataAnnotations.Schema;
using Microsoft.Build.Framework;

namespace Geld_Guardian.Pages.Data.Models
{
    [Table("bills")]
    public class Bill
    {
        public int BillId { get; set; }
        public string StoreName { get; set; }
        public string BillingNumber { get; set; }
        public DateTime BillDate { get; set; }
        public DateTime? DueDate { get; set; }
        public string Status { get; set; } = "Paid"; // Default status
        public string Category { get; set; }
        public string PaymentMethod { get; set; }

        // Navigation property to access related BillItems
        public List<BillItem> BillItems { get; set; } = new List<BillItem>();
    }
}
