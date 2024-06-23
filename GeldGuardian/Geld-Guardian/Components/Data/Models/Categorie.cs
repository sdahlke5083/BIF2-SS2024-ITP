using EntityFrameworkCore.Projectables;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;

namespace Geld_Guardian.Components.Data.Models
{
    [PrimaryKey("CategorieId")]
    public class Categorie
    {
        public int CategorieId { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        // Earnings specific field(s)
        /// <summary>
        /// Set to true if the category is for earnings/income only.
        /// Set to false if the category is for expenses only.
        /// Default: false
        /// </summary>
        public bool EarningsInsteadOfExpenses { get; set; } = false;
        [Projectable]
        public bool IsForExpenses => !EarningsInsteadOfExpenses;
        [Projectable]
        public bool IsForEarnings => EarningsInsteadOfExpenses;

        // one to many relationship with BillItem and Bill
        public ICollection<BillItem> BillItems { get; set; }
        public ICollection<Bill> Bills { get; set; }

        public override string ToString()
        {
            return Name;
        }
    }
}
