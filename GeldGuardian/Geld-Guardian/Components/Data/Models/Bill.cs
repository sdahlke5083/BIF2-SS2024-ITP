using System.Collections.Generic;
using System;
using Microsoft.EntityFrameworkCore;
using System.ComponentModel.DataAnnotations.Schema;
using Microsoft.Build.Framework;
using Microsoft.AspNetCore.Identity;
using EntityFrameworkCore.Projectables;
using System.Linq;

namespace Geld_Guardian.Components.Data.Models
{
    [Table("bills")]
    public class Bill
    {
        public int BillId { get; set; }
        public string UserId { get; set; }
        public string StoreName { get; set; }
        public string BillingNumber { get; set; }
        public DateTime BillDate { get; set; }
        public DateTime? DueDate { get; set; }
        public int StatusId { get; set; } = 1;
        public int CategoryId { get; set; } = 1;
        public int PaymentMethodId { get; set; } = 1;
        [Projectable]
        public decimal TotalAmount => BillItems.Sum(bi => bi.TotalPrice);
        // Earnings specific field(s)
        public decimal? Netto { get; set; }

        // Navigation property to access related BillItems
        public List<BillItem> BillItems { get; set; } = [];
        // Foreign key to access related User   
        public IdentityUser User { get; set; }
        //Foreign key to access related 
        public PaymentStatus Status { get; set; }
        public Categorie Category { get; set; }
        public PaymentMethod PaymentMethod { get; set; }

    }
}
